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
struct pool {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  retry_on_resume (struct bio*) ; 
 scalar_t__ should_error_unserviceable_bio (struct pool*) ; 

__attribute__((used)) static void handle_unserviceable_bio(struct pool *pool, struct bio *bio)
{
	if (should_error_unserviceable_bio(pool))
		bio_io_error(bio);
	else
		retry_on_resume(bio);
}