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
struct wahc {int /*<<< orphan*/  usb_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_get_intf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct wahc *wa_get(struct wahc *wa)
{
	usb_get_intf(wa->usb_iface);
	return wa;
}