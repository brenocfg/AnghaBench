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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct gfs2_rgrp {int dummy; } ;
struct gfs2_rbm {int offset; TYPE_3__* bi; TYPE_2__* rgd; } ;
struct gfs2_meta_header {int dummy; } ;
struct TYPE_6__ {int bi_len; } ;
struct TYPE_5__ {scalar_t__ rd_data0; scalar_t__ rd_data; TYPE_1__* rd_sbd; TYPE_3__* rd_bits; } ;
struct TYPE_4__ {int sd_blocks_per_bitmap; } ;

/* Variables and functions */
 int E2BIG ; 
 int GFS2_NBBY ; 

__attribute__((used)) static int gfs2_rbm_from_block(struct gfs2_rbm *rbm, u64 block)
{
	u32 x;

	if (block >= rbm->rgd->rd_data0 + rbm->rgd->rd_data)
		return -E2BIG;

	rbm->bi = rbm->rgd->rd_bits;
	rbm->offset = (u32)(block - rbm->rgd->rd_data0);
	/* Check if the block is within the first block */
	if (rbm->offset < rbm->bi->bi_len * GFS2_NBBY)
		return 0;

	/* Adjust for the size diff between gfs2_meta_header and gfs2_rgrp */
	rbm->offset += (sizeof(struct gfs2_rgrp) -
			sizeof(struct gfs2_meta_header)) * GFS2_NBBY;
	x = rbm->offset / rbm->rgd->rd_sbd->sd_blocks_per_bitmap;
	rbm->offset -= x * rbm->rgd->rd_sbd->sd_blocks_per_bitmap;
	rbm->bi += x;
	return 0;
}