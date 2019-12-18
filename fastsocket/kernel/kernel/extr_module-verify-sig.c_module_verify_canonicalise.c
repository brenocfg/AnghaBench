#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct module_verify_data {int* canonlist; int nsects; int* canonmap; int sig_index; char* secstrings; int ncanon; TYPE_1__* sections; } ;
struct TYPE_2__ {int sh_flags; scalar_t__ sh_type; size_t sh_info; int sh_name; } ;
typedef  TYPE_1__ Elf_Shdr ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SHF_ALLOC ; 
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int module_verify_canonicalise(struct module_verify_data *mvdata)
{
	int canon, loop, changed, tmp;

	/* produce a list of index numbers of sections that contribute
	 * to the kernel's module image
	 */
	mvdata->canonlist =
		kmalloc(sizeof(int) * mvdata->nsects * 2, GFP_KERNEL);
	if (!mvdata->canonlist)
		return -ENOMEM;

	mvdata->canonmap = mvdata->canonlist + mvdata->nsects;
	canon = 0;

	for (loop = 1; loop < mvdata->nsects; loop++) {
		const Elf_Shdr *section = mvdata->sections + loop;

		if (loop == mvdata->sig_index)
			continue;

		/* we only need to canonicalise allocatable sections */
		if (section->sh_flags & SHF_ALLOC)
			mvdata->canonlist[canon++] = loop;
		else if ((section->sh_type == SHT_REL ||
			  section->sh_type == SHT_RELA) &&
			 mvdata->sections[section->sh_info].sh_flags & SHF_ALLOC)
			mvdata->canonlist[canon++] = loop;
	}

	/* canonicalise the index numbers of the contributing section */
	do {
		changed = 0;

		for (loop = 0; loop < canon - 1; loop++) {
			const char *x, *y;

			x = mvdata->secstrings +
				mvdata->sections[mvdata->canonlist[loop + 0]].sh_name;
			y = mvdata->secstrings +
				mvdata->sections[mvdata->canonlist[loop + 1]].sh_name;

			if (strcmp(x, y) > 0) {
				tmp = mvdata->canonlist[loop + 0];
				mvdata->canonlist[loop + 0] =
					mvdata->canonlist[loop + 1];
				mvdata->canonlist[loop + 1] = tmp;
				changed = 1;
			}
		}

	} while (changed);

	for (loop = 0; loop < canon; loop++)
		mvdata->canonmap[mvdata->canonlist[loop]] = loop + 1;
	mvdata->ncanon = canon;
	return 0;
}