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
struct TYPE_3__ {int /*<<< orphan*/ ** rx_pool; } ;
typedef  TYPE_1__ pegasus_t ;

/* Variables and functions */
 int RX_SKBS ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_skb_pool(pegasus_t * pegasus)
{
	int i;

	for (i = 0; i < RX_SKBS; i++) {
		if (pegasus->rx_pool[i]) {
			dev_kfree_skb(pegasus->rx_pool[i]);
			pegasus->rx_pool[i] = NULL;
		}
	}
}