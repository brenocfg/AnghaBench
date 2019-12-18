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
struct urb {int /*<<< orphan*/  status; struct rt2x00_async_read_data* context; } ;
struct rt2x00_async_read_data {int /*<<< orphan*/  reg; int /*<<< orphan*/  rt2x00dev; scalar_t__ (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct rt2x00_async_read_data*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2x00usb_register_read_async_cb(struct urb *urb)
{
	struct rt2x00_async_read_data *rd = urb->context;
	if (rd->callback(rd->rt2x00dev, urb->status, le32_to_cpu(rd->reg))) {
		if (usb_submit_urb(urb, GFP_ATOMIC) < 0)
			kfree(rd);
	} else
		kfree(rd);
}