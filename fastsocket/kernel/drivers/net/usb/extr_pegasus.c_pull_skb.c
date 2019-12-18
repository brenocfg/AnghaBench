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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {struct sk_buff** rx_pool; } ;
typedef  TYPE_1__ pegasus_t ;

/* Variables and functions */
 int RX_SKBS ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff *pull_skb(pegasus_t * pegasus)
{
	int i;
	struct sk_buff *skb;

	for (i = 0; i < RX_SKBS; i++) {
		if (likely(pegasus->rx_pool[i] != NULL)) {
			skb = pegasus->rx_pool[i];
			pegasus->rx_pool[i] = NULL;
			return skb;
		}
	}
	return NULL;
}