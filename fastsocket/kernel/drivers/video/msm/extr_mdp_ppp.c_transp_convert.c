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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ format; } ;
struct mdp_blit_req {int /*<<< orphan*/  transp_mask; TYPE_1__ src; } ;

/* Variables and functions */
 int GET_BIT_RANGE (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ MDP_RGB_565 ; 

__attribute__((used)) static uint32_t transp_convert(struct mdp_blit_req *req)
{
	uint32_t transp = 0;
	if (req->src.format == MDP_RGB_565) {
		/* pad each value to 8 bits by copying the high bits into the
		 * low end, convert RGB to RBG by switching low 2 components */
		transp |= ((GET_BIT_RANGE(req->transp_mask, 15, 11) << 3) |
			   (GET_BIT_RANGE(req->transp_mask, 15, 13))) << 16;

		transp |= ((GET_BIT_RANGE(req->transp_mask, 4, 0) << 3) |
			   (GET_BIT_RANGE(req->transp_mask, 4, 2))) << 8;

		transp |= (GET_BIT_RANGE(req->transp_mask, 10, 5) << 2) |
			  (GET_BIT_RANGE(req->transp_mask, 10, 9));
	} else {
		/* convert RGB to RBG */
		transp |= (GET_BIT_RANGE(req->transp_mask, 15, 8)) |
			  (GET_BIT_RANGE(req->transp_mask, 23, 16) << 16) |
			  (GET_BIT_RANGE(req->transp_mask, 7, 0) << 8);
	}
	return transp;
}