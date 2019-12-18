#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
struct section {char* name; scalar_t__ addr; int /*<<< orphan*/  scn; } ;
struct readelf {size_t shnum; struct section* sl; } ;
struct TYPE_4__ {size_t d_size; int* d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  HEX_DUMP ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_dumpop (struct readelf*,size_t,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hex_dump(struct readelf *re)
{
	struct section *s;
	Elf_Data *d;
	uint8_t *buf;
	size_t sz, nbytes;
	uint64_t addr;
	int elferr, i, j;

	for (i = 1; (size_t) i < re->shnum; i++) {
		s = &re->sl[i];
		if (find_dumpop(re, (size_t) i, s->name, HEX_DUMP, -1) == NULL)
			continue;
		(void) elf_errno();
		if ((d = elf_getdata(s->scn, NULL)) == NULL &&
		    (d = elf_rawdata(s->scn, NULL)) == NULL) {
			elferr = elf_errno();
			if (elferr != 0)
				warnx("elf_getdata failed: %s",
				    elf_errmsg(elferr));
			continue;
		}
		(void) elf_errno();
		if (d->d_size <= 0 || d->d_buf == NULL) {
			printf("\nSection '%s' has no data to dump.\n",
			    s->name);
			continue;
		}
		buf = d->d_buf;
		sz = d->d_size;
		addr = s->addr;
		printf("\nHex dump of section '%s':\n", s->name);
		while (sz > 0) {
			printf("  0x%8.8jx ", (uintmax_t)addr);
			nbytes = sz > 16? 16 : sz;
			for (j = 0; j < 16; j++) {
				if ((size_t)j < nbytes)
					printf("%2.2x", buf[j]);
				else
					printf("  ");
				if ((j & 3) == 3)
					printf(" ");
			}
			for (j = 0; (size_t)j < nbytes; j++) {
				if (isprint(buf[j]))
					printf("%c", buf[j]);
				else
					printf(".");
			}
			printf("\n");
			buf += nbytes;
			addr += nbytes;
			sz -= nbytes;
		}
	}
}