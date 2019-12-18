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
struct usb_mixer_elem_info {int control; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_GET_CUR ; 
 int get_ctl_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static inline int get_cur_mix_raw(struct usb_mixer_elem_info *cval,
				  int channel, int *value)
{
	return get_ctl_value(cval, UAC_GET_CUR, (cval->control << 8) | channel, value);
}