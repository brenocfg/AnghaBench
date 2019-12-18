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
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ io_overlaps_block (struct pool*,struct bio*) ; 

__attribute__((used)) static int io_overwrites_block(struct pool *pool, struct bio *bio)
{
	return (bio_data_dir(bio) == WRITE) &&
		io_overlaps_block(pool, bio);
}