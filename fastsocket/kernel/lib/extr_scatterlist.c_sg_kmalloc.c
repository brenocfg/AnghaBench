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
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned int SG_MAX_SINGLE_ALLOC ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 struct scatterlist* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct scatterlist *sg_kmalloc(unsigned int nents, gfp_t gfp_mask)
{
	if (nents == SG_MAX_SINGLE_ALLOC)
		return (struct scatterlist *) __get_free_page(gfp_mask);
	else
		return kmalloc(nents * sizeof(struct scatterlist), gfp_mask);
}