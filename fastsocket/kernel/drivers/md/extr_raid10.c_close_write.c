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
struct r10bio {TYPE_1__* mddev; int /*<<< orphan*/  state; int /*<<< orphan*/  sectors; int /*<<< orphan*/  sector; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  R10BIO_Degraded ; 
 int /*<<< orphan*/  bitmap_endwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_write_end (TYPE_1__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_write(struct r10bio *r10_bio)
{
	/* clear the bitmap if all writes complete successfully */
	bitmap_endwrite(r10_bio->mddev->bitmap, r10_bio->sector,
			r10_bio->sectors,
			!test_bit(R10BIO_Degraded, &r10_bio->state),
			0);
	md_write_end(r10_bio->mddev);
}