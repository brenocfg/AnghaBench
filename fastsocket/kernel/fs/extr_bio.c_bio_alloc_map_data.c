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
struct sg_iovec {int dummy; } ;
struct bio_vec {int dummy; } ;
struct bio_map_data {struct bio_map_data* iovecs; void* sgvecs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bio_map_data*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bio_map_data *bio_alloc_map_data(int nr_segs, int iov_count,
					       gfp_t gfp_mask)
{
	struct bio_map_data *bmd = kmalloc(sizeof(*bmd), gfp_mask);

	if (!bmd)
		return NULL;

	bmd->iovecs = kmalloc(sizeof(struct bio_vec) * nr_segs, gfp_mask);
	if (!bmd->iovecs) {
		kfree(bmd);
		return NULL;
	}

	bmd->sgvecs = kmalloc(sizeof(struct sg_iovec) * iov_count, gfp_mask);
	if (bmd->sgvecs)
		return bmd;

	kfree(bmd->iovecs);
	kfree(bmd);
	return NULL;
}