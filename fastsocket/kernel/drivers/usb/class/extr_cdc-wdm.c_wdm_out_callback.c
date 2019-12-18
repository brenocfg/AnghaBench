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
struct wdm_device {int /*<<< orphan*/  wait; int /*<<< orphan*/  outbuf; int /*<<< orphan*/  flags; int /*<<< orphan*/  iuspin; int /*<<< orphan*/  werr; } ;
struct urb {int /*<<< orphan*/  status; struct wdm_device* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDM_IN_USE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wdm_out_callback(struct urb *urb)
{
	struct wdm_device *desc;
	desc = urb->context;
	spin_lock(&desc->iuspin);
	desc->werr = urb->status;
	spin_unlock(&desc->iuspin);
	clear_bit(WDM_IN_USE, &desc->flags);
	kfree(desc->outbuf);
	wake_up(&desc->wait);
}