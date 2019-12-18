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
typedef  TYPE_1__* uthread_t ;
struct _throttle_io_info_t {scalar_t__ throttle_io_periods; scalar_t__ throttle_disabled; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int uu_lowpri_window; int /*<<< orphan*/  uu_throttle_bc; struct _throttle_io_info_t* uu_throttle_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ALLOC_THROTTLE_INFO (char*,struct _throttle_io_info_t*,struct _throttle_io_info_t*) ; 
 scalar_t__ lowpri_throttle_enabled ; 
 int /*<<< orphan*/  throttle_info_ref (struct _throttle_io_info_t*) ; 
 int /*<<< orphan*/  throttle_init_throttle_period (struct _throttle_io_info_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void throttle_info_set_initial_window(uthread_t ut, struct _throttle_io_info_t *info, boolean_t BC_throttle, boolean_t isssd)
{
	if (lowpri_throttle_enabled == 0 || info->throttle_disabled)
		return;

	if (info->throttle_io_periods == 0) {
		throttle_init_throttle_period(info, isssd);
	}
	if (ut->uu_throttle_info == NULL) {

		ut->uu_throttle_info = info;
		throttle_info_ref(info);
		DEBUG_ALLOC_THROTTLE_INFO("updating info = %p\n", info, info );

		ut->uu_lowpri_window = 1;
		ut->uu_throttle_bc = BC_throttle;
	}
}