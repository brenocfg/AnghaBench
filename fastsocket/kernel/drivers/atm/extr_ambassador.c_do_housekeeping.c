#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  housekeeping; } ;
typedef  TYPE_1__ amb_dev ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  fill_rx_pools (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void do_housekeeping (unsigned long arg) {
  amb_dev * dev = (amb_dev *) arg;
  
  // could collect device-specific (not driver/atm-linux) stats here
      
  // last resort refill once every ten seconds
  fill_rx_pools (dev);
  mod_timer(&dev->housekeeping, jiffies + 10*HZ);
  
  return;
}