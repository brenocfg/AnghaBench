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
typedef  TYPE_1__* uthread_t ;
struct _throttle_io_info_t {int dummy; } ;
struct TYPE_4__ {int uu_throttle_bc; scalar_t__ uu_lowpri_window; struct _throttle_io_info_t* uu_throttle_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 TYPE_1__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throttle_info_rel (struct _throttle_io_info_t*) ; 

void throttle_info_reset_window(uthread_t ut)
{
	struct _throttle_io_info_t *info;

	if (ut == NULL) 
		ut = get_bsdthread_info(current_thread());

	if ( (info = ut->uu_throttle_info) ) {
		throttle_info_rel(info);

		ut->uu_throttle_info = NULL;
		ut->uu_lowpri_window = 0;
		ut->uu_throttle_bc = false;
	}
}