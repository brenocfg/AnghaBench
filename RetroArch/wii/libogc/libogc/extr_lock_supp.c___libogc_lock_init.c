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
typedef  scalar_t__ s32 ;
typedef  scalar_t__ mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LWP_MUTEX_NULL ; 
 scalar_t__ LWP_MutexInit (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

int __libogc_lock_init(int *lock,int recursive)
{
	s32 ret;
	mutex_t retlck = LWP_MUTEX_NULL;

	if(!lock) return -1;

	*lock = 0;
	ret = LWP_MutexInit(&retlck,(recursive?TRUE:FALSE));
	if(ret==0) *lock = (int)retlck;

	return ret;
}