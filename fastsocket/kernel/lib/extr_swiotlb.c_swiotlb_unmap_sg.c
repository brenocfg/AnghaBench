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
struct device {int dummy; } ;

/* Variables and functions */
 void swiotlb_unmap_sg_attrs (struct device*,struct scatterlist*,int,int,int /*<<< orphan*/ *) ; 

void
swiotlb_unmap_sg(struct device *hwdev, struct scatterlist *sgl, int nelems,
		 int dir)
{
	return swiotlb_unmap_sg_attrs(hwdev, sgl, nelems, dir, NULL);
}