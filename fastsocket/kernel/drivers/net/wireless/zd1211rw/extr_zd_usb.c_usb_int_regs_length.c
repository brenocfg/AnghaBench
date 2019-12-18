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
struct usb_int_regs {int dummy; } ;
struct reg_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int usb_int_regs_length(unsigned int count)
{
	return sizeof(struct usb_int_regs) + count * sizeof(struct reg_data);
}