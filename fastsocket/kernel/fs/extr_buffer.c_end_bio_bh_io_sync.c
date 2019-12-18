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
struct buffer_head {int /*<<< orphan*/  (* b_end_io ) (struct buffer_head*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  b_state; } ;
struct bio {int /*<<< orphan*/  bi_flags; struct buffer_head* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Eopnotsupp ; 
 int /*<<< orphan*/  BH_Quiet ; 
 int /*<<< orphan*/  BIO_EOPNOTSUPP ; 
 int /*<<< orphan*/  BIO_QUIET ; 
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_bio_bh_io_sync(struct bio *bio, int err)
{
	struct buffer_head *bh = bio->bi_private;

	if (err == -EOPNOTSUPP) {
		set_bit(BIO_EOPNOTSUPP, &bio->bi_flags);
		set_bit(BH_Eopnotsupp, &bh->b_state);
	}

	if (unlikely (test_bit(BIO_QUIET,&bio->bi_flags)))
		set_bit(BH_Quiet, &bh->b_state);

	bh->b_end_io(bh, test_bit(BIO_UPTODATE, &bio->bi_flags));
	bio_put(bio);
}