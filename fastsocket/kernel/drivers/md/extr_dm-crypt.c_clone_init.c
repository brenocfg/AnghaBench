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
struct dm_crypt_io {TYPE_1__* base_bio; TYPE_2__* target; } ;
struct crypt_config {TYPE_3__* dev; } ;
struct bio {int /*<<< orphan*/  bi_destructor; int /*<<< orphan*/  bi_rw; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_end_io; struct dm_crypt_io* bi_private; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {struct crypt_config* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_rw; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypt_endio ; 
 int /*<<< orphan*/  dm_crypt_bio_destructor ; 

__attribute__((used)) static void clone_init(struct dm_crypt_io *io, struct bio *clone)
{
	struct crypt_config *cc = io->target->private;

	clone->bi_private = io;
	clone->bi_end_io  = crypt_endio;
	clone->bi_bdev    = cc->dev->bdev;
	clone->bi_rw      = io->base_bio->bi_rw;
	clone->bi_destructor = dm_crypt_bio_destructor;
}