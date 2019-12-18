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
struct stripe_head {struct r5dev* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bv_page; } ;
struct TYPE_4__ {struct stripe_head* bi_private; int /*<<< orphan*/  bi_max_vecs; int /*<<< orphan*/  bi_vcnt; TYPE_1__* bi_io_vec; } ;
struct r5dev {int /*<<< orphan*/  sector; scalar_t__ flags; int /*<<< orphan*/  page; TYPE_1__ rvec; TYPE_2__ rreq; TYPE_1__ vec; TYPE_2__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_init (TYPE_2__*) ; 
 int /*<<< orphan*/  compute_blocknr (struct stripe_head*,int,int) ; 

__attribute__((used)) static void raid5_build_block(struct stripe_head *sh, int i, int previous)
{
	struct r5dev *dev = &sh->dev[i];

	bio_init(&dev->req);
	dev->req.bi_io_vec = &dev->vec;
	dev->req.bi_vcnt++;
	dev->req.bi_max_vecs++;
	dev->req.bi_private = sh;
	dev->vec.bv_page = dev->page;

	bio_init(&dev->rreq);
	dev->rreq.bi_io_vec = &dev->rvec;
	dev->rreq.bi_vcnt++;
	dev->rreq.bi_max_vecs++;
	dev->rreq.bi_private = sh;
	dev->rvec.bv_page = dev->page;

	dev->flags = 0;
	dev->sector = compute_blocknr(sh, i, previous);
}