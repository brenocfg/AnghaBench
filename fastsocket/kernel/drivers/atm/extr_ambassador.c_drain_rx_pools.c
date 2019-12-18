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
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_POOL ; 
 unsigned char NUM_RX_POOLS ; 
 int /*<<< orphan*/  PRINTD (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_rx_pool (int /*<<< orphan*/ *,unsigned char) ; 

__attribute__((used)) static void drain_rx_pools (amb_dev * dev) {
  unsigned char pool;
  
  PRINTD (DBG_FLOW|DBG_POOL, "drain_rx_pools %p", dev);
  
  for (pool = 0; pool < NUM_RX_POOLS; ++pool)
    drain_rx_pool (dev, pool);
}