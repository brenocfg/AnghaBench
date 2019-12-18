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
struct Port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_DEBUG_DELAY ; 
 int RIO_FAIL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

int RIODelay(struct Port *PortP, int njiffies)
{
	func_enter();

	rio_dprintk(RIO_DEBUG_DELAY, "delaying %d jiffies\n", njiffies);
	msleep_interruptible(jiffies_to_msecs(njiffies));
	func_exit();

	if (signal_pending(current))
		return RIO_FAIL;
	else
		return !RIO_FAIL;
}