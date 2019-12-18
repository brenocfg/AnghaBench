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
struct dma_pub {int dummy; } ;
struct dma_info {int /*<<< orphan*/  name; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 struct sk_buff* _dma_getnextrxp (struct dma_info*,int) ; 
 int /*<<< orphan*/  brcms_dbg_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 

void dma_rxreclaim(struct dma_pub *pub)
{
	struct dma_info *di = (struct dma_info *)pub;
	struct sk_buff *p;

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	while ((p = _dma_getnextrxp(di, true)))
		brcmu_pkt_buf_free_skb(p);
}