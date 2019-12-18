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
struct wacom_features {int dummy; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 struct wacom_features* wacom_features ; 
 struct usb_device_id const* wacom_ids ; 

struct wacom_features * get_wacom_feature(const struct usb_device_id *id)
{
        int index = id - wacom_ids;
        struct wacom_features *wf = &wacom_features[index];

        return wf;
}