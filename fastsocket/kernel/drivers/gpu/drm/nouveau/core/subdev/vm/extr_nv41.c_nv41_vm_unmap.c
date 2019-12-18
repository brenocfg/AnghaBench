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
typedef  int u32 ;
struct nouveau_gpuobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 

__attribute__((used)) static void
nv41_vm_unmap(struct nouveau_gpuobj *pgt, u32 pte, u32 cnt)
{
	pte = pte * 4;
	while (cnt--) {
		nv_wo32(pgt, pte, 0x00000000);
		pte += 4;
	}
}