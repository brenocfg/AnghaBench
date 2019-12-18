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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct section {int /*<<< orphan*/  scn; } ;
struct TYPE_9__ {int /*<<< orphan*/ * e_ident; } ;
struct readelf {TYPE_1__ ehdr; int /*<<< orphan*/  elf; } ;
struct TYPE_10__ {int d_size; int* d_buf; int /*<<< orphan*/  d_type; } ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 size_t EI_DATA ; 
 int /*<<< orphan*/  ELF_T_XWORD ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_2__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 TYPE_2__* gelf_xlatetom (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
dump_svr4_hash64(struct readelf *re, struct section *s)
{
	Elf_Data	*d, dst;
	uint64_t	*buf;
	uint64_t	 nbucket, nchain;
	uint64_t	*bucket, *chain;
	uint64_t	*bl, *c, maxl, total;
	int		 elferr, i, j;

	/*
	 * ALPHA uses 64-bit hash entries. Since libelf assumes that
	 * .hash section contains only 32-bit entry, an explicit
	 * gelf_xlatetom is needed here.
	 */
	(void) elf_errno();
	if ((d = elf_rawdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_rawdata failed: %s",
			    elf_errmsg(elferr));
		return;
	}
	d->d_type = ELF_T_XWORD;
	memcpy(&dst, d, sizeof(Elf_Data));
	if (gelf_xlatetom(re->elf, &dst, d,
		re->ehdr.e_ident[EI_DATA]) != &dst) {
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
	if (d->d_size != (nbucket + nchain + 2) * sizeof(uint32_t)) {
		warnx("Malformed .hash section");
		return;
	}
	bucket = &buf[2];
	chain = &buf[2 + nbucket];

	maxl = 0;
	if ((bl = calloc(nbucket, sizeof(*bl))) == NULL)
		errx(EXIT_FAILURE, "calloc failed");
	for (i = 0; (uint32_t)i < nbucket; i++)
		for (j = bucket[i]; j > 0 && (uint32_t)j < nchain; j = chain[j])
			if (++bl[i] > maxl)
				maxl = bl[i];
	if ((c = calloc(maxl + 1, sizeof(*c))) == NULL)
		errx(EXIT_FAILURE, "calloc failed");
	for (i = 0; (uint64_t)i < nbucket; i++)
		c[bl[i]]++;
	printf("Histogram for bucket list length (total of %ju buckets):\n",
	    (uintmax_t)nbucket);
	printf(" Length\tNumber\t\t%% of total\tCoverage\n");
	total = 0;
	for (i = 0; (uint64_t)i <= maxl; i++) {
		total += c[i] * i;
		printf("%7u\t%-10ju\t(%5.1f%%)\t%5.1f%%\n", i, (uintmax_t)c[i],
		    c[i] * 100.0 / nbucket, total * 100.0 / (nchain - 1));
	}
	free(c);
	free(bl);
}