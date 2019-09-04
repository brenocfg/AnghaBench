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
struct TYPE_3__ {scalar_t__ grp_attr_val; } ;
typedef  TYPE_1__ lck_grp_attr_t ;

/* Variables and functions */
 scalar_t__ LCK_GRP_ATTR_STAT ; 
 int LcksOpts ; 
 int enaLkStat ; 

void
lck_grp_attr_setdefault(
	lck_grp_attr_t	*attr)
{
	if (LcksOpts & enaLkStat)
		attr->grp_attr_val = LCK_GRP_ATTR_STAT;
	else
		attr->grp_attr_val = 0;
}