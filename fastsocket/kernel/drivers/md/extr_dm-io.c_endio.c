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
struct io {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  dec_count (struct io*,unsigned int,int) ; 
 int /*<<< orphan*/  retrieve_io_and_region_from_bio (struct bio*,struct io**,unsigned int*) ; 
 int /*<<< orphan*/  zero_fill_bio (struct bio*) ; 

__attribute__((used)) static void endio(struct bio *bio, int error)
{
	struct io *io;
	unsigned region;

	if (error && bio_data_dir(bio) == READ)
		zero_fill_bio(bio);

	/*
	 * The bio destructor in bio_put() may use the io object.
	 */
	retrieve_io_and_region_from_bio(bio, &io, &region);

	bio_put(bio);

	dec_count(io, region, error);
}