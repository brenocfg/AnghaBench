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
typedef  int /*<<< orphan*/  u32 ;
struct iovm_struct {int dummy; } ;
struct iommu {int /*<<< orphan*/  mmap_lock; } ;

/* Variables and functions */
 struct iovm_struct* __find_iovm_area (struct iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct iovm_struct *find_iovm_area(struct iommu *obj, u32 da)
{
	struct iovm_struct *area;

	mutex_lock(&obj->mmap_lock);
	area = __find_iovm_area(obj, da);
	mutex_unlock(&obj->mmap_lock);

	return area;
}