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
struct dev_state {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int usb_reset_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_resetdevice(struct dev_state *ps)
{
	return usb_reset_device(ps->dev);
}