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
typedef  int /*<<< orphan*/  mutex_st ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_MAX_MUTEXES ; 
 int /*<<< orphan*/  __lwp_objmgr_initinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _lwp_mutex_objects ; 

void __lwp_mutex_init()
{
	__lwp_objmgr_initinfo(&_lwp_mutex_objects,LWP_MAX_MUTEXES,sizeof(mutex_st));
}