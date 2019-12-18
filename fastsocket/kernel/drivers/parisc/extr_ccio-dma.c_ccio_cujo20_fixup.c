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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct parisc_device {int dummy; } ;
struct ioc {int cujo20_bug; int* res_map; unsigned int res_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUJO_20_STEP ; 
 int PDIR_INDEX (int /*<<< orphan*/ ) ; 
 struct ioc* ccio_get_iommu (struct parisc_device*) ; 
 struct parisc_device* parisc_parent (struct parisc_device*) ; 

void ccio_cujo20_fixup(struct parisc_device *cujo, u32 iovp)
{
	unsigned int idx;
	struct parisc_device *dev = parisc_parent(cujo);
	struct ioc *ioc = ccio_get_iommu(dev);
	u8 *res_ptr;

	ioc->cujo20_bug = 1;
	res_ptr = ioc->res_map;
	idx = PDIR_INDEX(iovp) >> 3;

	while (idx < ioc->res_size) {
 		res_ptr[idx] |= 0xff;
		idx += PDIR_INDEX(CUJO_20_STEP) >> 3;
	}
}