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
struct tty_struct {int index; int low_latency; int count; struct slgt_info* driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int count; int flags; struct tty_struct* tty; int /*<<< orphan*/  close_wait; } ;
struct slgt_info {int line; int /*<<< orphan*/  device_name; TYPE_1__ port; int /*<<< orphan*/  netlock; scalar_t__ netcount; scalar_t__ init_error; struct slgt_info* next_device; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ASYNC_CLOSING ; 
 int ASYNC_HUP_NOTIFY ; 
 long ASYNC_LOW_LATENCY ; 
 int /*<<< orphan*/  DBGERR (char*) ; 
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int block_til_ready (struct tty_struct*,struct file*,struct slgt_info*) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int slgt_device_count ; 
 struct slgt_info* slgt_device_list ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int startup (struct slgt_info*) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 

__attribute__((used)) static int open(struct tty_struct *tty, struct file *filp)
{
	struct slgt_info *info;
	int retval, line;
	unsigned long flags;

	line = tty->index;
	if ((line < 0) || (line >= slgt_device_count)) {
		DBGERR(("%s: open with invalid line #%d.\n", driver_name, line));
		return -ENODEV;
	}

	info = slgt_device_list;
	while(info && info->line != line)
		info = info->next_device;
	if (sanity_check(info, tty->name, "open"))
		return -ENODEV;
	if (info->init_error) {
		DBGERR(("%s init error=%d\n", info->device_name, info->init_error));
		return -ENODEV;
	}

	tty->driver_data = info;
	info->port.tty = tty;

	DBGINFO(("%s open, old ref count = %d\n", info->device_name, info->port.count));

	/* If port is closing, signal caller to try again */
	if (tty_hung_up_p(filp) || info->port.flags & ASYNC_CLOSING){
		if (info->port.flags & ASYNC_CLOSING)
			interruptible_sleep_on(&info->port.close_wait);
		retval = ((info->port.flags & ASYNC_HUP_NOTIFY) ?
			-EAGAIN : -ERESTARTSYS);
		goto cleanup;
	}

	info->port.tty->low_latency = (info->port.flags & ASYNC_LOW_LATENCY) ? 1 : 0;

	spin_lock_irqsave(&info->netlock, flags);
	if (info->netcount) {
		retval = -EBUSY;
		spin_unlock_irqrestore(&info->netlock, flags);
		goto cleanup;
	}
	info->port.count++;
	spin_unlock_irqrestore(&info->netlock, flags);

	if (info->port.count == 1) {
		/* 1st open on this device, init hardware */
		retval = startup(info);
		if (retval < 0)
			goto cleanup;
	}

	retval = block_til_ready(tty, filp, info);
	if (retval) {
		DBGINFO(("%s block_til_ready rc=%d\n", info->device_name, retval));
		goto cleanup;
	}

	retval = 0;

cleanup:
	if (retval) {
		if (tty->count == 1)
			info->port.tty = NULL; /* tty layer will release tty struct */
		if(info->port.count)
			info->port.count--;
	}

	DBGINFO(("%s open rc=%d\n", info->device_name, retval));
	return retval;
}