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
struct wusbhc {int /*<<< orphan*/  usb_hcd; } ;

/* Variables and functions */
 scalar_t__ usb_get_hcd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct wusbhc *wusbhc_get(struct wusbhc *wusbhc)
{
	return usb_get_hcd(&wusbhc->usb_hcd) ? wusbhc : NULL;
}