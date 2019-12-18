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
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  lwp_cntrl ;
struct TYPE_2__ {scalar_t__ min_id; scalar_t__ max_id; scalar_t__* local_table; } ;

/* Variables and functions */
 TYPE_1__ _lwp_thr_objects ; 
 int /*<<< orphan*/ * _thr_idle ; 

lwp_cntrl* gdbstub_indextoid(s32 thread)
{
	s32 min_id,max_id,first_id;
	lwp_cntrl *th;

	if(thread<=0) return NULL;

	if(thread==1) return _thr_idle;

	first_id = 1;
	min_id = _lwp_thr_objects.min_id;
	max_id = _lwp_thr_objects.max_id;
	if(thread<(first_id + (max_id - min_id))) {
		th = (lwp_cntrl*)_lwp_thr_objects.local_table[thread - first_id];
		return th;
	}
	return NULL;
}