#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ uid; struct TYPE_7__* fow; } ;
typedef  TYPE_2__ USRT ;
struct TYPE_6__ {scalar_t__ st_uid; } ;
struct TYPE_8__ {TYPE_1__ sb; } ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 unsigned int USR_TB_SZ ; 
 TYPE_2__** usrtb ; 

__attribute__((used)) static int
usr_match(ARCHD *arcn)
{
	USRT *pt;

	/*
	 * hash and look for it in the table
	 */
	pt = usrtb[((unsigned)arcn->sb.st_uid) % USR_TB_SZ];
	while (pt != NULL) {
		if (pt->uid == arcn->sb.st_uid)
			return(0);
		pt = pt->fow;
	}

	/*
	 * not found
	 */
	return(1);
}