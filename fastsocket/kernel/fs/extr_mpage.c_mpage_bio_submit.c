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
struct bio {int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int WRITE ; 
 int /*<<< orphan*/  mpage_end_io_read ; 
 int /*<<< orphan*/  mpage_end_io_write ; 
 int /*<<< orphan*/  submit_bio (int,struct bio*) ; 

__attribute__((used)) static struct bio *mpage_bio_submit(int rw, struct bio *bio)
{
	bio->bi_end_io = mpage_end_io_read;
	if (rw == WRITE)
		bio->bi_end_io = mpage_end_io_write;
	submit_bio(rw, bio);
	return NULL;
}