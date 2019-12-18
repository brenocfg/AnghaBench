#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mdp_regs {int src_rect; int src0; int src1; int src_ystride; int src_cfg; int src_pack; int op; int phasex_init; int phasey_init; int phasex_step; int phasey_step; int dst_cfg; int dst_pack; int dst_rect; int dst0; int dst1; int dst_ystride; int edge; } ;
struct mdp_info {int dummy; } ;
struct TYPE_2__ {size_t format; } ;
struct mdp_blit_req {int alpha; int transp_mask; TYPE_1__ dst; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int MDP_DISPLAY0_START ; 
 int PPP_ADDR_ALPHA_TRANSP ; 
 int PPP_ADDR_BG0 ; 
 int PPP_ADDR_BG1 ; 
 int PPP_ADDR_BG_CFG ; 
 int PPP_ADDR_BG_PACK_PATTERN ; 
 int PPP_ADDR_BG_YSTRIDE ; 
 int PPP_ADDR_DST0 ; 
 int PPP_ADDR_DST1 ; 
 int PPP_ADDR_DST_CFG ; 
 int PPP_ADDR_DST_PACK_PATTERN ; 
 int PPP_ADDR_DST_ROI ; 
 int PPP_ADDR_DST_YSTRIDE ; 
 int PPP_ADDR_EDGE ; 
 int PPP_ADDR_OPERATION ; 
 int PPP_ADDR_PHASEX_INIT ; 
 int PPP_ADDR_PHASEX_STEP ; 
 int PPP_ADDR_PHASEY_INIT ; 
 int PPP_ADDR_PHASEY_STEP ; 
 int PPP_ADDR_SRC0 ; 
 int PPP_ADDR_SRC1 ; 
 int PPP_ADDR_SRC_CFG ; 
 int PPP_ADDR_SRC_PACK_PATTERN ; 
 int PPP_ADDR_SRC_ROI ; 
 int PPP_ADDR_SRC_YSTRIDE ; 
 int PPP_OP_BLEND_ON ; 
 int /*<<< orphan*/  flush_imgs (struct mdp_blit_req*,struct mdp_regs*,struct file*,struct file*) ; 
 int /*<<< orphan*/  mdp_writel (struct mdp_info const*,int,int) ; 
 int* pack_pattern ; 
 int* src_img_cfg ; 

__attribute__((used)) static int send_blit(const struct mdp_info *mdp, struct mdp_blit_req *req,
		     struct mdp_regs *regs, struct file *src_file,
		     struct file *dst_file)
{
	mdp_writel(mdp, 1, 0x060);
	mdp_writel(mdp, regs->src_rect, PPP_ADDR_SRC_ROI);
	mdp_writel(mdp, regs->src0, PPP_ADDR_SRC0);
	mdp_writel(mdp, regs->src1, PPP_ADDR_SRC1);
	mdp_writel(mdp, regs->src_ystride, PPP_ADDR_SRC_YSTRIDE);
	mdp_writel(mdp, regs->src_cfg, PPP_ADDR_SRC_CFG);
	mdp_writel(mdp, regs->src_pack, PPP_ADDR_SRC_PACK_PATTERN);

	mdp_writel(mdp, regs->op, PPP_ADDR_OPERATION);
	mdp_writel(mdp, regs->phasex_init, PPP_ADDR_PHASEX_INIT);
	mdp_writel(mdp, regs->phasey_init, PPP_ADDR_PHASEY_INIT);
	mdp_writel(mdp, regs->phasex_step, PPP_ADDR_PHASEX_STEP);
	mdp_writel(mdp, regs->phasey_step, PPP_ADDR_PHASEY_STEP);

	mdp_writel(mdp, (req->alpha << 24) | (req->transp_mask & 0xffffff),
	       PPP_ADDR_ALPHA_TRANSP);

	mdp_writel(mdp, regs->dst_cfg, PPP_ADDR_DST_CFG);
	mdp_writel(mdp, regs->dst_pack, PPP_ADDR_DST_PACK_PATTERN);
	mdp_writel(mdp, regs->dst_rect, PPP_ADDR_DST_ROI);
	mdp_writel(mdp, regs->dst0, PPP_ADDR_DST0);
	mdp_writel(mdp, regs->dst1, PPP_ADDR_DST1);
	mdp_writel(mdp, regs->dst_ystride, PPP_ADDR_DST_YSTRIDE);

	mdp_writel(mdp, regs->edge, PPP_ADDR_EDGE);
	if (regs->op & PPP_OP_BLEND_ON) {
		mdp_writel(mdp, regs->dst0, PPP_ADDR_BG0);
		mdp_writel(mdp, regs->dst1, PPP_ADDR_BG1);
		mdp_writel(mdp, regs->dst_ystride, PPP_ADDR_BG_YSTRIDE);
		mdp_writel(mdp, src_img_cfg[req->dst.format], PPP_ADDR_BG_CFG);
		mdp_writel(mdp, pack_pattern[req->dst.format],
			   PPP_ADDR_BG_PACK_PATTERN);
	}
	flush_imgs(req, regs, src_file, dst_file);
	mdp_writel(mdp, 0x1000, MDP_DISPLAY0_START);
	return 0;
}