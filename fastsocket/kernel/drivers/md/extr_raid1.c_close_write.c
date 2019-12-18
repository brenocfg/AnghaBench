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
struct r1bio {int behind_page_count; TYPE_1__* mddev; int /*<<< orphan*/  state; int /*<<< orphan*/  sectors; int /*<<< orphan*/  sector; TYPE_2__* behind_bvecs; } ;
struct TYPE_4__ {int /*<<< orphan*/  bv_page; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  R1BIO_BehindIO ; 
 int /*<<< orphan*/  R1BIO_Degraded ; 
 int /*<<< orphan*/  bitmap_endwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  md_write_end (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_write(struct r1bio *r1_bio)
{
	/* it really is the end of this request */
	if (test_bit(R1BIO_BehindIO, &r1_bio->state)) {
		/* free extra copy of the data pages */
		int i = r1_bio->behind_page_count;
		while (i--)
			safe_put_page(r1_bio->behind_bvecs[i].bv_page);
		kfree(r1_bio->behind_bvecs);
		r1_bio->behind_bvecs = NULL;
	}
	/* clear the bitmap if all writes complete successfully */
	bitmap_endwrite(r1_bio->mddev->bitmap, r1_bio->sector,
			r1_bio->sectors,
			!test_bit(R1BIO_Degraded, &r1_bio->state),
			test_bit(R1BIO_BehindIO, &r1_bio->state));
	md_write_end(r1_bio->mddev);
}