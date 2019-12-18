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
struct ar9170 {int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  cmd_lock; scalar_t__ readlen; int /*<<< orphan*/  tx_anch; TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_IDLE ; 
 int /*<<< orphan*/  CARL9170_STOPPED ; 
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_set_state_when (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int carl9170_usb_flush (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_handle_tx_err (struct ar9170*) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_poison_anchored_urbs (int /*<<< orphan*/ *) ; 

void carl9170_usb_stop(struct ar9170 *ar)
{
	int ret;

	carl9170_set_state_when(ar, CARL9170_IDLE, CARL9170_STOPPED);

	ret = carl9170_usb_flush(ar);
	if (ret)
		dev_err(&ar->udev->dev, "kill pending tx urbs.\n");

	usb_poison_anchored_urbs(&ar->tx_anch);
	carl9170_usb_handle_tx_err(ar);

	/* kill any pending command */
	spin_lock_bh(&ar->cmd_lock);
	ar->readlen = 0;
	spin_unlock_bh(&ar->cmd_lock);
	complete_all(&ar->cmd_wait);

	/* This is required to prevent an early completion on _start */
	INIT_COMPLETION(ar->cmd_wait);

	/*
	 * Note:
	 * So far we freed all tx urbs, but we won't dare to touch any rx urbs.
	 * Else we would end up with a unresponsive device...
	 */
}