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
struct aliasinfo {char* name; TYPE_1__* slab; } ;
struct TYPE_2__ {int refs; char* name; } ;

/* Variables and functions */
 int aliases ; 
 struct aliasinfo* aliasinfo ; 
 int /*<<< orphan*/  link_slabs () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_inverted ; 
 int /*<<< orphan*/  show_single_ref ; 
 int /*<<< orphan*/  sort_aliases () ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void alias(void)
{
	struct aliasinfo *a;
	char *active = NULL;

	sort_aliases();
	link_slabs();

	for(a = aliasinfo; a < aliasinfo + aliases; a++) {

		if (!show_single_ref && a->slab->refs == 1)
			continue;

		if (!show_inverted) {
			if (active) {
				if (strcmp(a->slab->name, active) == 0) {
					printf(" %s", a->name);
					continue;
				}
			}
			printf("\n%-12s <- %s", a->slab->name, a->name);
			active = a->slab->name;
		}
		else
			printf("%-20s -> %s\n", a->name, a->slab->name);
	}
	if (active)
		printf("\n");
}