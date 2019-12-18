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
struct dma_pub {int dummy; } ;
struct brcms_ampdu_session {int /*<<< orphan*/  skb_list; } ;
struct dma_info {struct brcms_ampdu_session ampdu_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  ampdu_finalize (struct dma_info*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

void dma_txflush(struct dma_pub *pub)
{
	struct dma_info *di = (struct dma_info *)pub;
	struct brcms_ampdu_session *session = &di->ampdu_session;

	if (!skb_queue_empty(&session->skb_list))
		ampdu_finalize(di);
}