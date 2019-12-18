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
struct slabinfo {int dummy; } ;
struct aliasinfo {int /*<<< orphan*/  name; struct slabinfo* slab; } ;

/* Variables and functions */
 int aliases ; 
 struct aliasinfo* aliasinfo ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct aliasinfo *find_one_alias(struct slabinfo *find)
{
	struct aliasinfo *a;
	struct aliasinfo *best = NULL;

	for(a = aliasinfo;a < aliasinfo + aliases; a++) {
		if (a->slab == find &&
			(!best || strlen(best->name) < strlen(a->name))) {
				best = a;
				if (strncmp(a->name,"kmall", 5) == 0)
					return best;
			}
	}
	return best;
}