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
struct dm_target {struct crypt_config* private; } ;
struct dm_crypt_io {int /*<<< orphan*/  pending; int /*<<< orphan*/ * base_io; scalar_t__ error; int /*<<< orphan*/  sector; struct bio* base_bio; struct dm_target* target; } ;
struct crypt_config {int /*<<< orphan*/  io_pool; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dm_crypt_io* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_crypt_io *crypt_io_alloc(struct dm_target *ti,
					  struct bio *bio, sector_t sector)
{
	struct crypt_config *cc = ti->private;
	struct dm_crypt_io *io;

	io = mempool_alloc(cc->io_pool, GFP_NOIO);
	io->target = ti;
	io->base_bio = bio;
	io->sector = sector;
	io->error = 0;
	io->base_io = NULL;
	atomic_set(&io->pending, 0);

	return io;
}