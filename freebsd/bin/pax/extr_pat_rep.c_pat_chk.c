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
struct TYPE_3__ {int flgs; char* pstr; struct TYPE_3__* fow; } ;
typedef  TYPE_1__ PATTERN ;

/* Variables and functions */
 int MTCH ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* pathead ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
pat_chk(void)
{
	PATTERN *pt;
	int wban = 0;

	/*
	 * walk down the list checking the flags to make sure MTCH was set,
	 * if not complain
	 */
	for (pt = pathead; pt != NULL; pt = pt->fow) {
		if (pt->flgs & MTCH)
			continue;
		if (!wban) {
			paxwarn(1, "WARNING! These patterns were not matched:");
			++wban;
		}
		(void)fprintf(stderr, "%s\n", pt->pstr);
	}
}