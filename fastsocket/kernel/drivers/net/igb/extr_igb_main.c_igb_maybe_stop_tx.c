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
typedef  scalar_t__ u16 ;
struct igb_ring {int dummy; } ;

/* Variables and functions */
 int __igb_maybe_stop_tx (struct igb_ring*,scalar_t__ const) ; 
 scalar_t__ const igb_desc_unused (struct igb_ring*) ; 

__attribute__((used)) static inline int igb_maybe_stop_tx(struct igb_ring *tx_ring, const u16 size)
{
	if (igb_desc_unused(tx_ring) >= size)
		return 0;
	return __igb_maybe_stop_tx(tx_ring, size);
}