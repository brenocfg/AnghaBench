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
struct pvr2_ctrl {TYPE_1__* hdw; } ;
struct TYPE_2__ {int /*<<< orphan*/  big_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int pvr2_ctrl_value_to_sym_internal (struct pvr2_ctrl*,int,int,char*,unsigned int,unsigned int*) ; 

int pvr2_ctrl_value_to_sym(struct pvr2_ctrl *cptr,
			   int mask,int val,
			   char *buf,unsigned int maxlen,
			   unsigned int *len)
{
	int ret;
	LOCK_TAKE(cptr->hdw->big_lock); do {
		ret = pvr2_ctrl_value_to_sym_internal(cptr,mask,val,
						      buf,maxlen,len);
	} while(0); LOCK_GIVE(cptr->hdw->big_lock);
	return ret;
}