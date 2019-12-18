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
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 struct usb_device_id* wacom_ids ; 

const struct usb_device_id *get_device_table(void)
{
        const struct usb_device_id *id_table = wacom_ids;

        return id_table;
}