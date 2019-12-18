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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  flush_page_for_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_get_scsi_one (struct device*,char*,unsigned long) ; 

__attribute__((used)) static __u32 iommu_get_scsi_one_gflush(struct device *dev, char *vaddr, unsigned long len)
{
	flush_page_for_dma(0);
	return iommu_get_scsi_one(dev, vaddr, len);
}