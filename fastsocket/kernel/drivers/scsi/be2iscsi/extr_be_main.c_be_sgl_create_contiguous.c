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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct be_dma_mem {unsigned long dma; scalar_t__ size; void* va; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int
be_sgl_create_contiguous(void *virtual_address,
			 u64 physical_address, u32 length,
			 struct be_dma_mem *sgl)
{
	WARN_ON(!virtual_address);
	WARN_ON(!physical_address);
	WARN_ON(!length > 0);
	WARN_ON(!sgl);

	sgl->va = virtual_address;
	sgl->dma = (unsigned long)physical_address;
	sgl->size = length;

	return 0;
}