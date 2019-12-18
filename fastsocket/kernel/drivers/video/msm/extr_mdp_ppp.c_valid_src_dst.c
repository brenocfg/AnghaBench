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
typedef  unsigned long uint32_t ;
struct mdp_regs {unsigned long src0; int src_cfg; unsigned long src1; unsigned long dst0; int dst_cfg; unsigned long dst1; int /*<<< orphan*/  dst_bpp; int /*<<< orphan*/  src_bpp; } ;
struct mdp_blit_req {int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_rect; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int PPP_SRC_PLANE_PSEUDOPLNR ; 
 int /*<<< orphan*/  get_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 

__attribute__((used)) static int valid_src_dst(unsigned long src_start, unsigned long src_len,
			 unsigned long dst_start, unsigned long dst_len,
			 struct mdp_blit_req *req, struct mdp_regs *regs)
{
	unsigned long src_min_ok = src_start;
	unsigned long src_max_ok = src_start + src_len;
	unsigned long dst_min_ok = dst_start;
	unsigned long dst_max_ok = dst_start + dst_len;
	uint32_t src0_len, src1_len, dst0_len, dst1_len;
	get_len(&req->src, &req->src_rect, regs->src_bpp, &src0_len,
		 &src1_len);
	get_len(&req->dst, &req->dst_rect, regs->dst_bpp, &dst0_len,
		 &dst1_len);

	if (regs->src0 < src_min_ok || regs->src0 > src_max_ok ||
	    regs->src0 + src0_len > src_max_ok) {
		DLOG("invalid_src %x %x %lx %lx\n", regs->src0,
		      src0_len, src_min_ok, src_max_ok);
		return 0;
	}
	if (regs->src_cfg & PPP_SRC_PLANE_PSEUDOPLNR) {
		if (regs->src1 < src_min_ok || regs->src1 > src_max_ok ||
		    regs->src1 + src1_len > src_max_ok) {
			DLOG("invalid_src1");
			return 0;
		}
	}
	if (regs->dst0 < dst_min_ok || regs->dst0 > dst_max_ok ||
	    regs->dst0 + dst0_len > dst_max_ok) {
		DLOG("invalid_dst");
		return 0;
	}
	if (regs->dst_cfg & PPP_SRC_PLANE_PSEUDOPLNR) {
		if (regs->dst1 < dst_min_ok || regs->dst1 > dst_max_ok ||
		    regs->dst1 + dst1_len > dst_max_ok) {
			DLOG("invalid_dst1");
			return 0;
		}
	}
	return 1;
}