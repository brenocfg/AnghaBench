#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_queue; } ;
typedef  TYPE_1__ hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TX ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_busy ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tx_hold (hrz_dev * dev) {
  PRINTD (DBG_TX, "sleeping at tx lock %p %lu", dev, dev->flags);
  wait_event_interruptible(dev->tx_queue, (!test_and_set_bit(tx_busy, &dev->flags)));
  PRINTD (DBG_TX, "woken at tx lock %p %lu", dev, dev->flags);
  if (signal_pending (current))
    return -1;
  PRINTD (DBG_TX, "set tx_busy for dev %p", dev);
  return 0;
}