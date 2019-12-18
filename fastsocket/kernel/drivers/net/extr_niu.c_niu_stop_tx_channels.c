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
struct tx_ring_info {int dummy; } ;
struct niu {int num_tx_rings; struct tx_ring_info* tx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  niu_stop_one_tx_channel (struct niu*,struct tx_ring_info*) ; 

__attribute__((used)) static void niu_stop_tx_channels(struct niu *np)
{
	int i;

	for (i = 0; i < np->num_tx_rings; i++) {
		struct tx_ring_info *rp = &np->tx_rings[i];

		niu_stop_one_tx_channel(np, rp);
	}
}