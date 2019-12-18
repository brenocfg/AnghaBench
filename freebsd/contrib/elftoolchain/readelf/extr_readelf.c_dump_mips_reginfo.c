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
struct section {char* name; int /*<<< orphan*/  scn; } ;
struct readelf {int dummy; } ;
struct TYPE_3__ {scalar_t__ d_size; int /*<<< orphan*/  d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  dump_mips_odk_reginfo (struct readelf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_rawdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ent_count (struct section*,int*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_mips_reginfo(struct readelf *re, struct section *s)
{
	Elf_Data *d;
	int elferr, len;

	(void) elf_errno();
	if ((d = elf_rawdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_rawdata failed: %s",
			    elf_errmsg(elferr));
		return;
	}
	if (d->d_size <= 0)
		return;
	if (!get_ent_count(s, &len))
		return;

	printf("\nSection '%s' contains %d entries:\n", s->name, len);
	dump_mips_odk_reginfo(re, d->d_buf, d->d_size);
}