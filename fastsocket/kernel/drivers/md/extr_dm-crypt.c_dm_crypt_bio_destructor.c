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
struct dm_crypt_io {TYPE_1__* target; } ;
struct crypt_config {int /*<<< orphan*/  bs; } ;
struct bio {struct dm_crypt_io* bi_private; } ;
struct TYPE_2__ {struct crypt_config* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_free (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_crypt_bio_destructor(struct bio *bio)
{
	struct dm_crypt_io *io = bio->bi_private;
	struct crypt_config *cc = io->target->private;

	bio_free(bio, cc->bs);
}