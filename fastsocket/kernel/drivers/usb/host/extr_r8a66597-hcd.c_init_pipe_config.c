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
struct urb {int dummy; } ;
struct r8a66597_device {int /*<<< orphan*/  state; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_STATE_CONFIGURED ; 
 struct r8a66597_device* get_urb_to_r8a66597_dev (struct r8a66597*,struct urb*) ; 

__attribute__((used)) static void init_pipe_config(struct r8a66597 *r8a66597, struct urb *urb)
{
	struct r8a66597_device *dev;

	dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	dev->state = USB_STATE_CONFIGURED;
}