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
typedef  int u8 ;
struct be_adapter {int /*<<< orphan*/  mbox_lock; } ;

/* Variables and functions */
 int be_mbox_notify_wait (struct be_adapter*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wrb_from_mbox (struct be_adapter*) ; 

int be_cmd_fw_init(struct be_adapter *adapter)
{
	u8 *wrb;
	int status;

	if (lancer_chip(adapter))
		return 0;

	if (mutex_lock_interruptible(&adapter->mbox_lock))
		return -1;

	wrb = (u8 *)wrb_from_mbox(adapter);
	*wrb++ = 0xFF;
	*wrb++ = 0x12;
	*wrb++ = 0x34;
	*wrb++ = 0xFF;
	*wrb++ = 0xFF;
	*wrb++ = 0x56;
	*wrb++ = 0x78;
	*wrb = 0xFF;

	status = be_mbox_notify_wait(adapter);

	mutex_unlock(&adapter->mbox_lock);
	return status;
}