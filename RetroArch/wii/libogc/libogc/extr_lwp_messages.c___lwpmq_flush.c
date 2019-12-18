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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ num_pendingmsgs; } ;
typedef  TYPE_1__ mq_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __lwpmq_flush_support (TYPE_1__*) ; 

u32 __lwpmq_flush(mq_cntrl *mqueue)
{
	if(mqueue->num_pendingmsgs!=0)
		return __lwpmq_flush_support(mqueue);
	else
		return 0;
}