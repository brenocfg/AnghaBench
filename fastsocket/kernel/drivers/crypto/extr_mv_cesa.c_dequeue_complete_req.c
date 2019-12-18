#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* complete ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct ablkcipher_request {scalar_t__ nbytes; TYPE_2__ base; } ;
struct TYPE_8__ {void* addr; scalar_t__ length; } ;
struct TYPE_6__ {scalar_t__ total_req_bytes; scalar_t__ crypt_len; TYPE_3__ dst_sg_it; TYPE_3__ src_sg_it; scalar_t__ dst_start; scalar_t__ sg_dst_left; } ;
struct TYPE_9__ {scalar_t__ eng_st; TYPE_1__ p; scalar_t__ sram; struct ablkcipher_request* cur_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ENGINE_BUSY ; 
 scalar_t__ ENGINE_IDLE ; 
 scalar_t__ ENGINE_W_DEQUEUE ; 
 scalar_t__ SRAM_DATA_OUT_START ; 
 TYPE_5__* cpg ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mv_crypto_algo_completion () ; 
 int /*<<< orphan*/  mv_process_current_q (int /*<<< orphan*/ ) ; 
 int sg_miter_next (TYPE_3__*) ; 
 int /*<<< orphan*/  sg_miter_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dequeue_complete_req(void)
{
	struct ablkcipher_request *req = cpg->cur_req;
	void *buf;
	int ret;

	cpg->p.total_req_bytes += cpg->p.crypt_len;
	do {
		int dst_copy;

		if (!cpg->p.sg_dst_left) {
			ret = sg_miter_next(&cpg->p.dst_sg_it);
			BUG_ON(!ret);
			cpg->p.sg_dst_left = cpg->p.dst_sg_it.length;
			cpg->p.dst_start = 0;
		}

		buf = cpg->p.dst_sg_it.addr;
		buf += cpg->p.dst_start;

		dst_copy = min(cpg->p.crypt_len, cpg->p.sg_dst_left);

		memcpy(buf, cpg->sram + SRAM_DATA_OUT_START, dst_copy);

		cpg->p.sg_dst_left -= dst_copy;
		cpg->p.crypt_len -= dst_copy;
		cpg->p.dst_start += dst_copy;
	} while (cpg->p.crypt_len > 0);

	BUG_ON(cpg->eng_st != ENGINE_W_DEQUEUE);
	if (cpg->p.total_req_bytes < req->nbytes) {
		/* process next scatter list entry */
		cpg->eng_st = ENGINE_BUSY;
		mv_process_current_q(0);
	} else {
		sg_miter_stop(&cpg->p.src_sg_it);
		sg_miter_stop(&cpg->p.dst_sg_it);
		mv_crypto_algo_completion();
		cpg->eng_st = ENGINE_IDLE;
		req->base.complete(&req->base, 0);
	}
}