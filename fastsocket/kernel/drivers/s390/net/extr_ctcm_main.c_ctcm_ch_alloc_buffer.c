#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct channel {int /*<<< orphan*/  flags; TYPE_2__* trans_skb; int /*<<< orphan*/  trans_skb_data; TYPE_1__* ccw; int /*<<< orphan*/  id; scalar_t__ max_bufsize; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_DIRECTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHANNEL_FLAGS_BUFSIZE_CHANGED ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 scalar_t__ READ ; 
 TYPE_2__* __dev_alloc_skb (scalar_t__,int) ; 
 int /*<<< orphan*/  clear_normalized_cda (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 scalar_t__ set_normalized_cda (TYPE_1__*,int /*<<< orphan*/ ) ; 

int ctcm_ch_alloc_buffer(struct channel *ch)
{
	clear_normalized_cda(&ch->ccw[1]);
	ch->trans_skb = __dev_alloc_skb(ch->max_bufsize, GFP_ATOMIC | GFP_DMA);
	if (ch->trans_skb == NULL) {
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): %s trans_skb allocation error",
			CTCM_FUNTAIL, ch->id,
			(CHANNEL_DIRECTION(ch->flags) == READ) ? "RX" : "TX");
		return -ENOMEM;
	}

	ch->ccw[1].count = ch->max_bufsize;
	if (set_normalized_cda(&ch->ccw[1], ch->trans_skb->data)) {
		dev_kfree_skb(ch->trans_skb);
		ch->trans_skb = NULL;
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): %s set norm_cda failed",
			CTCM_FUNTAIL, ch->id,
			(CHANNEL_DIRECTION(ch->flags) == READ) ? "RX" : "TX");
		return -ENOMEM;
	}

	ch->ccw[1].count = 0;
	ch->trans_skb_data = ch->trans_skb->data;
	ch->flags &= ~CHANNEL_FLAGS_BUFSIZE_CHANGED;
	return 0;
}