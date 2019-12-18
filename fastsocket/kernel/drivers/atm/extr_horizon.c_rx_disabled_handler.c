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
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RX_CONFIG_OFF ; 
 int RX_ENABLE ; 
 int rd_regw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_regw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void rx_disabled_handler (hrz_dev * dev) {
  wr_regw (dev, RX_CONFIG_OFF, rd_regw (dev, RX_CONFIG_OFF) | RX_ENABLE);
  // count me please
  PRINTK (KERN_WARNING, "RX was disabled!");
}