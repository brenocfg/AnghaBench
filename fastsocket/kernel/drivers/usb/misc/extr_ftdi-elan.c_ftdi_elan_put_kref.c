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
struct usb_ftdi {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftdi_elan_delete ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftdi_elan_put_kref(struct usb_ftdi *ftdi)
{
        kref_put(&ftdi->kref, ftdi_elan_delete);
}