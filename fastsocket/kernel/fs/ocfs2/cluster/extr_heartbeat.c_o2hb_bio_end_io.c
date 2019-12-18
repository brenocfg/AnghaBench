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
struct o2hb_bio_wait_ctxt {int wc_error; } ;
struct bio {struct o2hb_bio_wait_ctxt* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  o2hb_bio_wait_dec (struct o2hb_bio_wait_ctxt*,int) ; 

__attribute__((used)) static void o2hb_bio_end_io(struct bio *bio,
			   int error)
{
	struct o2hb_bio_wait_ctxt *wc = bio->bi_private;

	if (error) {
		mlog(ML_ERROR, "IO Error %d\n", error);
		wc->wc_error = error;
	}

	o2hb_bio_wait_dec(wc, 1);
	bio_put(bio);
}