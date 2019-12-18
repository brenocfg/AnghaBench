#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lcs_header {int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {scalar_t__ buf_idx; scalar_t__ io_idx; int /*<<< orphan*/  state; TYPE_3__* ccws; TYPE_1__* iob; } ;
struct lcs_card {TYPE_2__ read; } ;
struct ccw1 {int dummy; } ;
typedef  void* __u32 ;
struct TYPE_7__ {int flags; void* cda; int /*<<< orphan*/  cmd_code; void* count; } ;
struct TYPE_5__ {void* count; int /*<<< orphan*/  state; int /*<<< orphan*/  callback; TYPE_3__* data; } ;

/* Variables and functions */
 int CCW_FLAG_CC ; 
 int CCW_FLAG_PCI ; 
 int CCW_FLAG_SLI ; 
 int CCW_FLAG_SUSPEND ; 
 int /*<<< orphan*/  LCS_BUF_STATE_READY ; 
 int /*<<< orphan*/  LCS_CCW_READ ; 
 int /*<<< orphan*/  LCS_CCW_TRANSFER ; 
 int /*<<< orphan*/  LCS_CH_STATE_INIT ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_ILLEGAL_OFFSET ; 
 void* LCS_IOBUFFERSIZE ; 
 int LCS_NUM_BUFFS ; 
 scalar_t__ __pa (TYPE_3__*) ; 
 int /*<<< orphan*/  lcs_get_frames_cb ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static void
lcs_setup_read_ccws(struct lcs_card *card)
{
	int cnt;

	LCS_DBF_TEXT(2, setup, "ireadccw");
	/* Setup read ccws. */
	memset(card->read.ccws, 0, sizeof (struct ccw1) * (LCS_NUM_BUFFS + 1));
	for (cnt = 0; cnt < LCS_NUM_BUFFS; cnt++) {
		card->read.ccws[cnt].cmd_code = LCS_CCW_READ;
		card->read.ccws[cnt].count = LCS_IOBUFFERSIZE;
		card->read.ccws[cnt].flags =
			CCW_FLAG_CC | CCW_FLAG_SLI | CCW_FLAG_PCI;
		/*
		 * Note: we have allocated the buffer with GFP_DMA, so
		 * we do not need to do set_normalized_cda.
		 */
		card->read.ccws[cnt].cda =
			(__u32) __pa(card->read.iob[cnt].data);
		((struct lcs_header *)
		 card->read.iob[cnt].data)->offset = LCS_ILLEGAL_OFFSET;
		card->read.iob[cnt].callback = lcs_get_frames_cb;
		card->read.iob[cnt].state = LCS_BUF_STATE_READY;
		card->read.iob[cnt].count = LCS_IOBUFFERSIZE;
	}
	card->read.ccws[0].flags &= ~CCW_FLAG_PCI;
	card->read.ccws[LCS_NUM_BUFFS - 1].flags &= ~CCW_FLAG_PCI;
	card->read.ccws[LCS_NUM_BUFFS - 1].flags |= CCW_FLAG_SUSPEND;
	/* Last ccw is a tic (transfer in channel). */
	card->read.ccws[LCS_NUM_BUFFS].cmd_code = LCS_CCW_TRANSFER;
	card->read.ccws[LCS_NUM_BUFFS].cda =
		(__u32) __pa(card->read.ccws);
	/* Setg initial state of the read channel. */
	card->read.state = LCS_CH_STATE_INIT;

	card->read.io_idx = 0;
	card->read.buf_idx = 0;
}