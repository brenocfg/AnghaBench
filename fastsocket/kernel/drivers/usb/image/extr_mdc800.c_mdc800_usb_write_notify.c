#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {int status; struct mdc800_data* context; } ;
struct mdc800_data {int written; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  state; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mdc800_usb_write_notify (struct urb *urb)
{
	struct mdc800_data* mdc800=urb->context;
	int status = urb->status;

	if (status != 0)
		dev_err(&mdc800->dev->dev,
			"writing command fails (status=%i)\n", status);
	else
		mdc800->state=READY;
	mdc800->written = 1;
	wake_up (&mdc800->write_wait);
}