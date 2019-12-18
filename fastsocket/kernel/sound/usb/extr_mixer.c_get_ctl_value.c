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
struct usb_mixer_elem_info {TYPE_1__* mixer; } ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ UAC_VERSION_1 ; 
 int get_ctl_value_v1 (struct usb_mixer_elem_info*,int,int,int*) ; 
 int get_ctl_value_v2 (struct usb_mixer_elem_info*,int,int,int*) ; 

__attribute__((used)) static int get_ctl_value(struct usb_mixer_elem_info *cval, int request, int validx, int *value_ret)
{
	return (cval->mixer->protocol == UAC_VERSION_1) ?
		get_ctl_value_v1(cval, request, validx, value_ret) :
		get_ctl_value_v2(cval, request, validx, value_ret);
}