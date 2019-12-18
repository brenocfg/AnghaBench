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
struct TYPE_2__ {int min_id; int max_id; } ;

/* Variables and functions */
 TYPE_1__ _lwp_thr_objects ; 
 scalar_t__ _thr_executing ; 
 scalar_t__ _thr_idle ; 

s32 gdbstub_idtoindex(s32 objid)
{
	s32 min_id,max_id;
	s32 first_id;

	if(_thr_executing==_thr_idle) return 1;

	first_id = 1;
	min_id = _lwp_thr_objects.min_id;
	max_id = _lwp_thr_objects.max_id;
	if(objid>=min_id && objid<max_id) return first_id + (objid - min_id);

	return 1;
}