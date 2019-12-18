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
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int dummy_g_get_frame (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dummy_h_get_frame (struct usb_hcd *hcd)
{
	return dummy_g_get_frame (NULL);
}