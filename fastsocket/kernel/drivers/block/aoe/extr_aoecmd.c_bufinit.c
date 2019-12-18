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
struct request {int dummy; } ;
struct buf {scalar_t__ bv_resid; TYPE_1__* bv; int /*<<< orphan*/  sector; int /*<<< orphan*/  resid; struct bio* bio; struct request* rq; } ;
struct bio {size_t bi_idx; TYPE_1__* bi_io_vec; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_size; } ;
struct TYPE_2__ {scalar_t__ bv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bio_pageinc (struct bio*) ; 
 int /*<<< orphan*/  memset (struct buf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bufinit(struct buf *buf, struct request *rq, struct bio *bio)
{
	memset(buf, 0, sizeof(*buf));
	buf->rq = rq;
	buf->bio = bio;
	buf->resid = bio->bi_size;
	buf->sector = bio->bi_sector;
	bio_pageinc(bio);
	buf->bv = &bio->bi_io_vec[bio->bi_idx];
	buf->bv_resid = buf->bv->bv_len;
	WARN_ON(buf->bv_resid == 0);
}