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
struct atp {int /*<<< orphan*/  urb; scalar_t__ open; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int atp_handle_geyser (struct atp*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atp_recover(struct atp *dev)
{
	int error;

	error = atp_handle_geyser(dev);
	if (error)
		return error;

	if (dev->open && usb_submit_urb(dev->urb, GFP_ATOMIC))
		return -EIO;

	return 0;
}