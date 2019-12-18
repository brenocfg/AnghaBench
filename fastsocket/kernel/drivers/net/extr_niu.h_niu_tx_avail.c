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
typedef  scalar_t__ u32 ;
struct tx_ring_info {int prod; int cons; scalar_t__ pending; } ;

/* Variables and functions */
 int MAX_TX_RING_SIZE ; 

__attribute__((used)) static inline u32 niu_tx_avail(struct tx_ring_info *tp)
{
	return (tp->pending -
		((tp->prod - tp->cons) & (MAX_TX_RING_SIZE - 1)));
}