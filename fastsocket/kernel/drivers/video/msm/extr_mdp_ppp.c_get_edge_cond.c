#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp_regs {int edge; int op; } ;
struct TYPE_4__ {scalar_t__ format; } ;
struct TYPE_6__ {int h; int y; int w; int x; } ;
struct TYPE_5__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct mdp_blit_req {int flags; TYPE_1__ src; TYPE_3__ src_rect; TYPE_2__ dst_rect; } ;
typedef  int int32_t ;

/* Variables and functions */
 size_t IMG_BOTTOM ; 
 size_t IMG_LEFT ; 
 size_t IMG_RIGHT ; 
 size_t IMG_TOP ; 
 scalar_t__ IS_YCRCB (scalar_t__) ; 
 int MDP_BOTTOM_CHROMA ; 
 int MDP_BOTTOM_LUMA ; 
 int MDP_LEFT_CHROMA ; 
 int MDP_LEFT_LUMA ; 
 int MDP_RIGHT_CHROMA ; 
 int MDP_RIGHT_LUMA ; 
 int MDP_ROT_90 ; 
 int MDP_TOP_CHROMA ; 
 int MDP_TOP_LUMA ; 
 scalar_t__ MDP_Y_CBCR_H2V2 ; 
 scalar_t__ MDP_Y_CRCB_H2V2 ; 
 int PPP_OP_SCALE_X_ON ; 
 int PPP_OP_SCALE_Y_ON ; 
 int /*<<< orphan*/  get_edge_info (int,int,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_edge_cond(struct mdp_blit_req *req, struct mdp_regs *regs)
{
	int32_t luma_interp[4];
	int32_t luma_repeat[4];
	int32_t chroma_interp[4];
	int32_t chroma_bound[4];
	int32_t chroma_repeat[4];
	uint32_t dst_w, dst_h;

	memset(&luma_interp, 0, sizeof(int32_t) * 4);
	memset(&luma_repeat, 0, sizeof(int32_t) * 4);
	memset(&chroma_interp, 0, sizeof(int32_t) * 4);
	memset(&chroma_bound, 0, sizeof(int32_t) * 4);
	memset(&chroma_repeat, 0, sizeof(int32_t) * 4);
	regs->edge = 0;

	if (req->flags & MDP_ROT_90) {
		dst_w = req->dst_rect.h;
		dst_h = req->dst_rect.w;
	} else {
		dst_w = req->dst_rect.w;
		dst_h = req->dst_rect.h;
	}

	if (regs->op & (PPP_OP_SCALE_Y_ON | PPP_OP_SCALE_X_ON)) {
		get_edge_info(req->src_rect.h, req->src_rect.y, dst_h,
			      &luma_interp[IMG_TOP], &luma_interp[IMG_BOTTOM],
			      &luma_repeat[IMG_TOP], &luma_repeat[IMG_BOTTOM]);
		get_edge_info(req->src_rect.w, req->src_rect.x, dst_w,
			      &luma_interp[IMG_LEFT], &luma_interp[IMG_RIGHT],
			      &luma_repeat[IMG_LEFT], &luma_repeat[IMG_RIGHT]);
	} else {
		luma_interp[IMG_LEFT] = req->src_rect.x;
		luma_interp[IMG_RIGHT] = req->src_rect.x + req->src_rect.w - 1;
		luma_interp[IMG_TOP] = req->src_rect.y;
		luma_interp[IMG_BOTTOM] = req->src_rect.y + req->src_rect.h - 1;
		luma_repeat[IMG_LEFT] = 0;
		luma_repeat[IMG_TOP] = 0;
		luma_repeat[IMG_RIGHT] = 0;
		luma_repeat[IMG_BOTTOM] = 0;
	}

	chroma_interp[IMG_LEFT] = luma_interp[IMG_LEFT];
	chroma_interp[IMG_RIGHT] = luma_interp[IMG_RIGHT];
	chroma_interp[IMG_TOP] = luma_interp[IMG_TOP];
	chroma_interp[IMG_BOTTOM] = luma_interp[IMG_BOTTOM];

	chroma_bound[IMG_LEFT] = req->src_rect.x;
	chroma_bound[IMG_RIGHT] = req->src_rect.x + req->src_rect.w - 1;
	chroma_bound[IMG_TOP] = req->src_rect.y;
	chroma_bound[IMG_BOTTOM] = req->src_rect.y + req->src_rect.h - 1;

	if (IS_YCRCB(req->src.format)) {
		chroma_interp[IMG_LEFT] = chroma_interp[IMG_LEFT] >> 1;
		chroma_interp[IMG_RIGHT] = (chroma_interp[IMG_RIGHT] + 1) >> 1;

		chroma_bound[IMG_LEFT] = chroma_bound[IMG_LEFT] >> 1;
		chroma_bound[IMG_RIGHT] = chroma_bound[IMG_RIGHT] >> 1;
	}

	if (req->src.format == MDP_Y_CBCR_H2V2 ||
	    req->src.format == MDP_Y_CRCB_H2V2) {
		chroma_interp[IMG_TOP] = (chroma_interp[IMG_TOP] - 1) >> 1;
		chroma_interp[IMG_BOTTOM] = (chroma_interp[IMG_BOTTOM] + 1)
					    >> 1;
		chroma_bound[IMG_TOP] = (chroma_bound[IMG_TOP] + 1) >> 1;
		chroma_bound[IMG_BOTTOM] = chroma_bound[IMG_BOTTOM] >> 1;
	}

	chroma_repeat[IMG_LEFT] = chroma_bound[IMG_LEFT] -
				  chroma_interp[IMG_LEFT];
	chroma_repeat[IMG_RIGHT] = chroma_interp[IMG_RIGHT] -
				  chroma_bound[IMG_RIGHT];
	chroma_repeat[IMG_TOP] = chroma_bound[IMG_TOP] -
				  chroma_interp[IMG_TOP];
	chroma_repeat[IMG_BOTTOM] = chroma_interp[IMG_BOTTOM] -
				  chroma_bound[IMG_BOTTOM];

	if (chroma_repeat[IMG_LEFT] < 0 || chroma_repeat[IMG_LEFT] > 3 ||
	    chroma_repeat[IMG_RIGHT] < 0 || chroma_repeat[IMG_RIGHT] > 3 ||
	    chroma_repeat[IMG_TOP] < 0 || chroma_repeat[IMG_TOP] > 3 ||
	    chroma_repeat[IMG_BOTTOM] < 0 || chroma_repeat[IMG_BOTTOM] > 3 ||
	    luma_repeat[IMG_LEFT] < 0 || luma_repeat[IMG_LEFT] > 3 ||
	    luma_repeat[IMG_RIGHT] < 0 || luma_repeat[IMG_RIGHT] > 3 ||
	    luma_repeat[IMG_TOP] < 0 || luma_repeat[IMG_TOP] > 3 ||
	    luma_repeat[IMG_BOTTOM] < 0 || luma_repeat[IMG_BOTTOM] > 3)
		return -1;

	regs->edge |= (chroma_repeat[IMG_LEFT] & 3) << MDP_LEFT_CHROMA;
	regs->edge |= (chroma_repeat[IMG_RIGHT] & 3) << MDP_RIGHT_CHROMA;
	regs->edge |= (chroma_repeat[IMG_TOP] & 3) << MDP_TOP_CHROMA;
	regs->edge |= (chroma_repeat[IMG_BOTTOM] & 3) << MDP_BOTTOM_CHROMA;
	regs->edge |= (luma_repeat[IMG_LEFT] & 3) << MDP_LEFT_LUMA;
	regs->edge |= (luma_repeat[IMG_RIGHT] & 3) << MDP_RIGHT_LUMA;
	regs->edge |= (luma_repeat[IMG_TOP] & 3) << MDP_TOP_LUMA;
	regs->edge |= (luma_repeat[IMG_BOTTOM] & 3) << MDP_BOTTOM_LUMA;
	return 0;
}