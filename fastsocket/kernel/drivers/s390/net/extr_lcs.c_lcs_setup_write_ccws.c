#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ buf_idx; scalar_t__ io_idx; TYPE_4__* ccws; TYPE_1__* iob; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct lcs_card {TYPE_3__ write; TYPE_2__ read; } ;
struct ccw1 {int dummy; } ;
typedef  void* __u32 ;
struct TYPE_9__ {int flags; void* cda; int /*<<< orphan*/  cmd_code; scalar_t__ count; } ;
struct TYPE_6__ {TYPE_4__* data; } ;

/* Variables and functions */
 int CCW_FLAG_CC ; 
 int CCW_FLAG_SLI ; 
 int CCW_FLAG_SUSPEND ; 
 int /*<<< orphan*/  LCS_CCW_TRANSFER ; 
 int /*<<< orphan*/  LCS_CCW_WRITE ; 
 int /*<<< orphan*/  LCS_CH_STATE_INIT ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int LCS_NUM_BUFFS ; 
 scalar_t__ __pa (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static void
lcs_setup_write_ccws(struct lcs_card *card)
{
	int cnt;

	LCS_DBF_TEXT(3, setup, "iwritccw");
	/* Setup write ccws. */
	memset(card->write.ccws, 0, sizeof(struct ccw1) * LCS_NUM_BUFFS + 1);
	for (cnt = 0; cnt < LCS_NUM_BUFFS; cnt++) {
		card->write.ccws[cnt].cmd_code = LCS_CCW_WRITE;
		card->write.ccws[cnt].count = 0;
		card->write.ccws[cnt].flags =
			CCW_FLAG_SUSPEND | CCW_FLAG_CC | CCW_FLAG_SLI;
		/*
		 * Note: we have allocated the buffer with GFP_DMA, so
		 * we do not need to do set_normalized_cda.
		 */
		card->write.ccws[cnt].cda =
			(__u32) __pa(card->write.iob[cnt].data);
	}
	/* Last ccw is a tic (transfer in channel). */
	card->write.ccws[LCS_NUM_BUFFS].cmd_code = LCS_CCW_TRANSFER;
	card->write.ccws[LCS_NUM_BUFFS].cda =
		(__u32) __pa(card->write.ccws);
	/* Set initial state of the write channel. */
	card->read.state = LCS_CH_STATE_INIT;

	card->write.io_idx = 0;
	card->write.buf_idx = 0;
}