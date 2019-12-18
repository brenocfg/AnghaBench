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
struct usb_mixer_elem_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_GET_CUR ; 
 int get_ctl_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int get_cur_ctl_value(struct usb_mixer_elem_info *cval, int validx, int *value)
{
	return get_ctl_value(cval, UAC_GET_CUR, validx, value);
}