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
struct sk_buff {int dummy; } ;
struct sbmacdma {int sbdma_maxdescr; struct sk_buff** sbdma_ctxtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void sbdma_emptyring(struct sbmacdma *d)
{
	int idx;
	struct sk_buff *sb;

	for (idx = 0; idx < d->sbdma_maxdescr; idx++) {
		sb = d->sbdma_ctxtable[idx];
		if (sb) {
			dev_kfree_skb(sb);
			d->sbdma_ctxtable[idx] = NULL;
		}
	}
}