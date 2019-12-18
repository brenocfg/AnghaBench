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
typedef  int u64 ;
typedef  int u32 ;
struct nouveau_vma {int dummy; } ;
struct nouveau_mem {int dummy; } ;
struct nouveau_gpuobj {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int NV41_GART_PAGE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 

__attribute__((used)) static void
nv41_vm_map_sg(struct nouveau_vma *vma, struct nouveau_gpuobj *pgt,
	       struct nouveau_mem *mem, u32 pte, u32 cnt, dma_addr_t *list)
{
	pte = pte * 4;
	while (cnt) {
		u32 page = PAGE_SIZE / NV41_GART_PAGE;
		u64 phys = (u64)*list++;
		while (cnt && page--) {
			nv_wo32(pgt, pte, (phys >> 7) | 1);
			phys += NV41_GART_PAGE;
			pte += 4;
			cnt -= 1;
		}
	}
}