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
struct dm_crypt_io {int error; TYPE_1__* target; } ;
struct crypt_config {int dummy; } ;
struct bio {struct dm_crypt_io* bi_private; } ;
struct TYPE_2__ {struct crypt_config* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int EIO ; 
 unsigned int READ ; 
 unsigned int WRITE ; 
 unsigned int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  crypt_dec_pending (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  crypt_free_buffer_pages (struct crypt_config*,struct bio*) ; 
 int /*<<< orphan*/  kcryptd_queue_crypt (struct dm_crypt_io*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void crypt_endio(struct bio *clone, int error)
{
	struct dm_crypt_io *io = clone->bi_private;
	struct crypt_config *cc = io->target->private;
	unsigned rw = bio_data_dir(clone);

	if (unlikely(!bio_flagged(clone, BIO_UPTODATE) && !error))
		error = -EIO;

	/*
	 * free the processed pages
	 */
	if (rw == WRITE)
		crypt_free_buffer_pages(cc, clone);

	bio_put(clone);

	if (rw == READ && !error) {
		kcryptd_queue_crypt(io);
		return;
	}

	if (unlikely(error))
		io->error = error;

	crypt_dec_pending(io);
}