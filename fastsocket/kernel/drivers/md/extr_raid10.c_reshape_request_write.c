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
struct r10conf {int copies; TYPE_1__* mirrors; } ;
struct r10bio {int /*<<< orphan*/  remaining; int /*<<< orphan*/  sectors; TYPE_2__* devs; int /*<<< orphan*/  state; } ;
struct mddev {struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;
struct bio {int /*<<< orphan*/ * bi_next; int /*<<< orphan*/  bi_bdev; } ;
struct TYPE_4__ {int devnum; struct bio* bio; struct bio* repl_bio; } ;
struct TYPE_3__ {struct md_rdev* rdev; struct md_rdev* replacement; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  R10BIO_Uptodate ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  end_reshape_request (struct r10bio*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 scalar_t__ handle_reshape_read_error (struct mddev*,struct r10bio*) ; 
 int /*<<< orphan*/  md_done_sync (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_sync_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reshape_request_write(struct mddev *mddev, struct r10bio *r10_bio)
{
	/* Reshape read completed.  Hopefully we have a block
	 * to write out.
	 * If we got a read error then we do sync 1-page reads from
	 * elsewhere until we find the data - or give up.
	 */
	struct r10conf *conf = mddev->private;
	int s;

	if (!test_bit(R10BIO_Uptodate, &r10_bio->state))
		if (handle_reshape_read_error(mddev, r10_bio) < 0) {
			/* Reshape has been aborted */
			md_done_sync(mddev, r10_bio->sectors, 0);
			return;
		}

	/* We definitely have the data in the pages, schedule the
	 * writes.
	 */
	atomic_set(&r10_bio->remaining, 1);
	for (s = 0; s < conf->copies*2; s++) {
		struct bio *b;
		int d = r10_bio->devs[s/2].devnum;
		struct md_rdev *rdev;
		if (s&1) {
			rdev = conf->mirrors[d].replacement;
			b = r10_bio->devs[s/2].repl_bio;
		} else {
			rdev = conf->mirrors[d].rdev;
			b = r10_bio->devs[s/2].bio;
		}
		if (!rdev || test_bit(Faulty, &rdev->flags))
			continue;
		atomic_inc(&rdev->nr_pending);
		md_sync_acct(b->bi_bdev, r10_bio->sectors);
		atomic_inc(&r10_bio->remaining);
		b->bi_next = NULL;
		generic_make_request(b);
	}
	end_reshape_request(r10_bio);
}