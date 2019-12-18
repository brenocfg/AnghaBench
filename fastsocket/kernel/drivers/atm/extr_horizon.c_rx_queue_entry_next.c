#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  mem_lock; TYPE_1__* rx_q_reset; TYPE_1__* rx_q_entry; TYPE_1__* rx_q_wrap; } ;
typedef  TYPE_2__ hrz_dev ;
struct TYPE_6__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_QUEUE_RD_PTR_OFF ; 
 int /*<<< orphan*/  rd_mem (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_regw (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 rx_queue_entry_next (hrz_dev * dev) {
  u32 rx_queue_entry;
  spin_lock (&dev->mem_lock);
  rx_queue_entry = rd_mem (dev, &dev->rx_q_entry->entry);
  if (dev->rx_q_entry == dev->rx_q_wrap)
    dev->rx_q_entry = dev->rx_q_reset;
  else
    dev->rx_q_entry++;
  wr_regw (dev, RX_QUEUE_RD_PTR_OFF, dev->rx_q_entry - dev->rx_q_reset);
  spin_unlock (&dev->mem_lock);
  return rx_queue_entry;
}