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
struct section {char* name; int /*<<< orphan*/  scn; } ;
struct readelf {size_t shnum; struct section* sl; } ;
struct TYPE_4__ {scalar_t__ d_size; int /*<<< orphan*/ * d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  STR_DUMP ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_dumpop (struct readelf*,size_t,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isprint (unsigned char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
str_dump(struct readelf *re)
{
	struct section *s;
	Elf_Data *d;
	unsigned char *start, *end, *buf_end;
	unsigned int len;
	int i, j, elferr, found;

	for (i = 1; (size_t) i < re->shnum; i++) {
		s = &re->sl[i];
		if (find_dumpop(re, (size_t) i, s->name, STR_DUMP, -1) == NULL)
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
		buf_end = (unsigned char *) d->d_buf + d->d_size;
		start = (unsigned char *) d->d_buf;
		found = 0;
		printf("\nString dump of section '%s':\n", s->name);
		for (;;) {
			while (start < buf_end && !isprint(*start))
				start++;
			if (start >= buf_end)
				break;
			end = start + 1;
			while (end < buf_end && isprint(*end))
				end++;
			printf("  [%6lx]  ",
			    (long) (start - (unsigned char *) d->d_buf));
			len = end - start;
			for (j = 0; (unsigned int) j < len; j++)
				putchar(start[j]);
			putchar('\n');
			found = 1;
			if (end >= buf_end)
				break;
			start = end + 1;
		}
		if (!found)
			printf("  No strings found in this section.");
		putchar('\n');
	}
}