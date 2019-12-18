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
struct bio {int /*<<< orphan*/  bi_destructor; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_fs_destructor ; 
 int /*<<< orphan*/  fs_bio_set ; 

struct bio *bio_alloc(gfp_t gfp_mask, int nr_iovecs)
{
	struct bio *bio = bio_alloc_bioset(gfp_mask, nr_iovecs, fs_bio_set);

	if (bio)
		bio->bi_destructor = bio_fs_destructor;

	return bio;
}