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
struct bio {int bi_rw; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int BIO_FUA ; 

__attribute__((used)) static bool blk_rq_should_init_elevator(struct bio *bio)
{
	if (!bio)
		return true;

	/*
	 * Flush requests do not use the elevator so skip initialization.
	 * This allows a request to share the flush and elevator data.
	 */
	if (bio->bi_rw & (BIO_FLUSH | BIO_FUA))
		return false;

	return true;
}