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
struct au1k_private {TYPE_1__* pDBfree; } ;
struct TYPE_3__ {struct TYPE_3__* pnext; } ;
typedef  TYPE_1__ db_dest_t ;

/* Variables and functions */

__attribute__((used)) static db_dest_t *GetFreeDB(struct au1k_private *aup)
{
	db_dest_t *pDB;
	pDB = aup->pDBfree;

	if (pDB) {
		aup->pDBfree = pDB->pnext;
	}
	return pDB;
}