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
typedef  int /*<<< orphan*/  cvmx_helper_board_usb_clock_types_t ;
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 128 
 int /*<<< orphan*/  USB_CLOCK_TYPE_CRYSTAL_12 ; 
 int /*<<< orphan*/  USB_CLOCK_TYPE_REF_48 ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

cvmx_helper_board_usb_clock_types_t __cvmx_helper_board_usb_get_clock_type(void)
{
	switch (cvmx_sysinfo_get()->board_type) {
	case CVMX_BOARD_TYPE_BBGW_REF:
		return USB_CLOCK_TYPE_CRYSTAL_12;
	}
	return USB_CLOCK_TYPE_REF_48;
}