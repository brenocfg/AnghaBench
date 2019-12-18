#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct req_progress {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst_sg_it; int /*<<< orphan*/  src_sg_it; } ;
struct TYPE_4__ {TYPE_1__ p; struct ablkcipher_request* cur_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_MITER_FROM_SG ; 
 int /*<<< orphan*/  SG_MITER_TO_SG ; 
 int count_sgs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cpg ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_process_current_q (int) ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_enqueue_new_req(struct ablkcipher_request *req)
{
	int num_sgs;

	cpg->cur_req = req;
	memset(&cpg->p, 0, sizeof(struct req_progress));

	num_sgs = count_sgs(req->src, req->nbytes);
	sg_miter_start(&cpg->p.src_sg_it, req->src, num_sgs, SG_MITER_FROM_SG);

	num_sgs = count_sgs(req->dst, req->nbytes);
	sg_miter_start(&cpg->p.dst_sg_it, req->dst, num_sgs, SG_MITER_TO_SG);
	mv_process_current_q(1);
}