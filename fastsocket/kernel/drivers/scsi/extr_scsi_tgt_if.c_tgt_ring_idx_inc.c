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
struct tgt_ring {int tr_idx; } ;

/* Variables and functions */
 int TGT_MAX_EVENTS ; 

__attribute__((used)) static inline void tgt_ring_idx_inc(struct tgt_ring *ring)
{
	if (ring->tr_idx == TGT_MAX_EVENTS - 1)
		ring->tr_idx = 0;
	else
		ring->tr_idx++;
}