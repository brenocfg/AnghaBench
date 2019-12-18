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
typedef  union map_info {int dummy; } map_info ;
struct dm_target {struct crypt_config* private; } ;
struct dm_crypt_io {int /*<<< orphan*/  base_bio; } ;
struct crypt_config {TYPE_1__* dev; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 scalar_t__ READ ; 
 scalar_t__ bio_data_dir (int /*<<< orphan*/ ) ; 
 struct dm_crypt_io* crypt_io_alloc (struct dm_target*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_target_offset (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcryptd_queue_crypt (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  kcryptd_queue_io (struct dm_crypt_io*) ; 

__attribute__((used)) static int crypt_map(struct dm_target *ti, struct bio *bio,
		     union map_info *map_context)
{
	struct dm_crypt_io *io;
	struct crypt_config *cc;

	if (bio->bi_rw & BIO_FLUSH) {
		cc = ti->private;
		bio->bi_bdev = cc->dev->bdev;
		return DM_MAPIO_REMAPPED;
	}

	io = crypt_io_alloc(ti, bio, dm_target_offset(ti, bio->bi_sector));

	if (bio_data_dir(io->base_bio) == READ)
		kcryptd_queue_io(io);
	else
		kcryptd_queue_crypt(io);

	return DM_MAPIO_SUBMITTED;
}