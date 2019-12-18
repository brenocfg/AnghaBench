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
struct _throttle_io_info_t {int throttle_disabled; scalar_t__ throttle_is_fusion_with_priority; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LOWPRI_MAX_NUM_DEV ; 
 struct _throttle_io_info_t* _throttle_io_info ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  throttle_init_throttle_period (struct _throttle_io_info_t*,int /*<<< orphan*/ ) ; 

void throttle_info_disable_throttle(int devno, boolean_t isfusion)
{
	struct _throttle_io_info_t *info;

	if (devno < 0 || devno >= LOWPRI_MAX_NUM_DEV) 
		panic("Illegal devno (%d) passed into throttle_info_disable_throttle()", devno);

	info = &_throttle_io_info[devno];
	// don't disable software throttling on devices that are part of a fusion device
	// and override the software throttle periods to use HDD periods
	if (isfusion) {
		info->throttle_is_fusion_with_priority = isfusion;
		throttle_init_throttle_period(info, FALSE);
	}
	info->throttle_disabled = !info->throttle_is_fusion_with_priority;
	return;
}