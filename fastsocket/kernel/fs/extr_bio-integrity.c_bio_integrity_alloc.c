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
struct bio_integrity_payload {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct bio_integrity_payload* bio_integrity_alloc_bioset (struct bio*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_bio_set ; 

struct bio_integrity_payload *bio_integrity_alloc(struct bio *bio,
						  gfp_t gfp_mask,
						  unsigned int nr_vecs)
{
	return bio_integrity_alloc_bioset(bio, gfp_mask, nr_vecs, fs_bio_set);
}