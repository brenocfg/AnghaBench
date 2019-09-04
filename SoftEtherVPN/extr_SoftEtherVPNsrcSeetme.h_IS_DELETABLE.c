#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; } ;
typedef  scalar_t__ int32 ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ enable_deletion; scalar_t__ filled_entries; scalar_t__ max_fill_state; TYPE_1__ last_read; } ;
typedef  TYPE_2__ TME_DATA ;

/* Variables and functions */
 scalar_t__ DELTA_READ ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static __inline int32 IS_DELETABLE(void *timestamp, TME_DATA *data)
{
	struct timeval *ts=(struct timeval*)timestamp;

	if (data->enable_deletion==FALSE)
		return FALSE;
	if (data->filled_entries<data->max_fill_state)
		return FALSE;
	if ((ts->tv_sec+DELTA_READ)<data->last_read.tv_sec)
		return TRUE;
	return FALSE;
}