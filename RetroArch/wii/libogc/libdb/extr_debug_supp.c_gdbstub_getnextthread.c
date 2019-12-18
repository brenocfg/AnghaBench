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
typedef  int s32 ;
struct TYPE_2__ {int min_id; int max_id; int /*<<< orphan*/ ** local_table; } ;

/* Variables and functions */
 TYPE_1__ _lwp_thr_objects ; 

s32 gdbstub_getnextthread(s32 athread)
{
	s32 id,start;
	s32 first_id,min_id,max_id,lim;

	if(athread<1) return 1;

	first_id = 1;
	min_id = _lwp_thr_objects.min_id;
	max_id = _lwp_thr_objects.max_id;
	lim = first_id + max_id - min_id;
	if(athread<lim) {
		if(athread<first_id)
			start = first_id;
		else
			start = athread+1;

		for(id=start;id<lim;id++)
			if(_lwp_thr_objects.local_table[id - first_id]!=NULL) return id;
	}

	return 0;
}