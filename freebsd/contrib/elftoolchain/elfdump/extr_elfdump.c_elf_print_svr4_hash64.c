#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uintmax_t ;
typedef  int uint64_t ;
struct section {int /*<<< orphan*/  link; int /*<<< orphan*/  scn; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/ * e_ident; } ;
struct elfdump {int flags; TYPE_1__ ehdr; int /*<<< orphan*/  elf; } ;
typedef  int /*<<< orphan*/  idx ;
struct TYPE_10__ {int d_size; int* d_buf; int /*<<< orphan*/  d_type; } ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 size_t EI_DATA ; 
 int /*<<< orphan*/  ELF_T_XWORD ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  PRT (char*,...) ; 
 int SOLARIS_FMT ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_2__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* gelf_xlatetom (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_symbol_name (struct elfdump*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
elf_print_svr4_hash64(struct elfdump *ed, struct section *s)
{
	Elf_Data	*data, dst;
	uint64_t	*buf;
	uint64_t	*bucket, *chain;
	uint64_t	 nbucket, nchain;
	uint64_t	*bl, *c, j, maxl, total;
	size_t		 i;
	int		 elferr, first;
	char		 idx[10];

	if (ed->flags & SOLARIS_FMT)
		PRT("\nHash Section:  %s\n", s->name);
	else
		PRT("\nhash table (%s):\n", s->name);

	/*
	 * ALPHA uses 64-bit hash entries. Since libelf assumes that
	 * .hash section contains only 32-bit entry, an explicit
	 * gelf_xlatetom is needed here.
	 */
	(void) elf_errno();
	if ((data = elf_rawdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_rawdata failed: %s",
			    elf_errmsg(elferr));
		return;
	}
	data->d_type = ELF_T_XWORD;
	memcpy(&dst, data, sizeof(Elf_Data));
	if (gelf_xlatetom(ed->elf, &dst, data,
		ed->ehdr.e_ident[EI_DATA]) != &dst) {
		warnx("gelf_xlatetom failed: %s", elf_errmsg(-1));
		return;
	}
	if (dst.d_size < 2 * sizeof(uint64_t)) {
		warnx(".hash section too small");
		return;
	}
	buf = dst.d_buf;
	nbucket = buf[0];
	nchain = buf[1];
	if (nbucket <= 0 || nchain <= 0) {
		warnx("Malformed .hash section");
		return;
	}
	if (dst.d_size != (nbucket + nchain + 2) * sizeof(uint64_t)) {
		warnx("Malformed .hash section");
		return;
	}
	bucket = &buf[2];
	chain = &buf[2 + nbucket];

	if (ed->flags & SOLARIS_FMT) {
		maxl = 0;
		if ((bl = calloc(nbucket, sizeof(*bl))) == NULL)
			err(EXIT_FAILURE, "calloc failed");
		for (i = 0; i < nbucket; i++)
			for (j = bucket[i]; j > 0 && j < nchain; j = chain[j])
				if (++bl[i] > maxl)
					maxl = bl[i];
		if ((c = calloc(maxl + 1, sizeof(*c))) == NULL)
			err(EXIT_FAILURE, "calloc failed");
		for (i = 0; i < nbucket; i++)
			c[bl[i]]++;
		PRT("    bucket    symndx    name\n");
		for (i = 0; i < nbucket; i++) {
			first = 1;
			for (j = bucket[i]; j > 0 && j < nchain; j = chain[j]) {
				if (first) {
					PRT("%10zu  ", i);
					first = 0;
				} else
					PRT("            ");
				snprintf(idx, sizeof(idx), "[%zu]", (size_t)j);
				PRT("%-10s  ", idx);
				PRT("%s\n", get_symbol_name(ed, s->link, j));
			}
		}
		PRT("\n");
		total = 0;
		for (i = 0; i <= maxl; i++) {
			total += c[i] * i;
			PRT("%10ju  buckets contain %8zu symbols\n",
			    (uintmax_t)c[i], i);
		}
		PRT("%10ju  buckets         %8ju symbols (globals)\n",
		    (uintmax_t)nbucket, (uintmax_t)total);
	} else {
		PRT("\nnbucket: %ju\n", (uintmax_t)nbucket);
		PRT("nchain: %ju\n\n", (uintmax_t)nchain);
		for (i = 0; i < nbucket; i++)
			PRT("bucket[%zu]:\n\t%ju\n\n", i, (uintmax_t)bucket[i]);
		for (i = 0; i < nchain; i++)
			PRT("chain[%zu]:\n\t%ju\n\n", i, (uintmax_t)chain[i]);
	}

}