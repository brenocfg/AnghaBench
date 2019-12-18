#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct aliasinfo {char* name; char* ref; } ;

/* Variables and functions */
 int aliases ; 
 struct aliasinfo* aliasinfo ; 
 int /*<<< orphan*/  memcpy (struct aliasinfo*,struct aliasinfo*,int) ; 
 scalar_t__ show_alias ; 
 int /*<<< orphan*/  show_inverted ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static void sort_aliases(void)
{
	struct aliasinfo *a1,*a2;

	for (a1 = aliasinfo; a1 < aliasinfo + aliases; a1++) {
		for (a2 = a1 + 1; a2 < aliasinfo + aliases; a2++) {
			char *n1, *n2;

			n1 = a1->name;
			n2 = a2->name;
			if (show_alias && !show_inverted) {
				n1 = a1->ref;
				n2 = a2->ref;
			}
			if (strcasecmp(n1, n2) > 0) {
				struct aliasinfo t;

				memcpy(&t, a1, sizeof(struct aliasinfo));
				memcpy(a1, a2, sizeof(struct aliasinfo));
				memcpy(a2, &t, sizeof(struct aliasinfo));
			}
		}
	}
}