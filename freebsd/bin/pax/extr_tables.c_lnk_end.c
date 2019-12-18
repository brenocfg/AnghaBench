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
struct TYPE_4__ {struct TYPE_4__* name; struct TYPE_4__* fow; } ;
typedef  TYPE_1__ HRDLNK ;

/* Variables and functions */
 int L_TAB_SZ ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__** ltab ; 

void
lnk_end(void)
{
	int i;
	HRDLNK *pt;
	HRDLNK *ppt;

	if (ltab == NULL)
		return;

	for (i = 0; i < L_TAB_SZ; ++i) {
		if (ltab[i] == NULL)
			continue;
		pt = ltab[i];
		ltab[i] = NULL;

		/*
		 * free up each entry on this chain
		 */
		while (pt != NULL) {
			ppt = pt;
			pt = ppt->fow;
			free(ppt->name);
			free(ppt);
		}
	}
	return;
}