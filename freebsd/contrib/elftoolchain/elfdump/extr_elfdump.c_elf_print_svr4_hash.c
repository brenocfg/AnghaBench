#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct section {int /*<<< orphan*/  link; int /*<<< orphan*/  scn; int /*<<< orphan*/  name; } ;
struct elfdump {int flags; } ;
typedef  int /*<<< orphan*/  idx ;
struct TYPE_3__ {int d_size; int* d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  PRT (char*,...) ; 
 int SOLARIS_FMT ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_symbol_name (struct elfdump*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
elf_print_svr4_hash(struct elfdump *ed, struct section *s)
{
	Elf_Data	*data;
	uint32_t	*buf;
	uint32_t	*bucket, *chain;
	uint32_t	 nbucket, nchain;
	uint32_t	*bl, *c, maxl, total;
	uint32_t	 i, j;
	int		 first, elferr;
	char		 idx[10];

	if (ed->flags & SOLARIS_FMT)
		PRT("\nHash Section:  %s\n", s->name);
	else
		PRT("\nhash table (%s):\n", s->name);
	(void) elf_errno();
	if ((data = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s",
			    elf_errmsg(elferr));
		return;
	}
	if (data->d_size < 2 * sizeof(uint32_t)) {
		warnx(".hash section too small");
		return;
	}
	buf = data->d_buf;
	nbucket = buf[0];
	nchain = buf[1];
	if (nbucket <= 0 || nchain <= 0) {
		warnx("Malformed .hash section");
		return;
	}
	if (data->d_size !=
	    ((uint64_t)nbucket + (uint64_t)nchain + 2) * sizeof(uint32_t)) {
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
					PRT("%10d  ", i);
					first = 0;
				} else
					PRT("            ");
				snprintf(idx, sizeof(idx), "[%d]", j);
				PRT("%-10s  ", idx);
				PRT("%s\n", get_symbol_name(ed, s->link, j));
			}
		}
		PRT("\n");
		total = 0;
		for (i = 0; i <= maxl; i++) {
			total += c[i] * i;
			PRT("%10u  buckets contain %8d symbols\n", c[i], i);
		}
		PRT("%10u  buckets         %8u symbols (globals)\n", nbucket,
		    total);
	} else {
		PRT("\nnbucket: %u\n", nbucket);
		PRT("nchain: %u\n\n", nchain);
		for (i = 0; i < nbucket; i++)
			PRT("bucket[%d]:\n\t%u\n\n", i, bucket[i]);
		for (i = 0; i < nchain; i++)
			PRT("chain[%d]:\n\t%u\n\n", i, chain[i]);
	}
}