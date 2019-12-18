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
typedef  int /*<<< orphan*/  u32 ;
struct nv04_instmem_priv {scalar_t__ iomem; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32_native (scalar_t__) ; 

__attribute__((used)) static u32
nv40_instmem_rd32(struct nouveau_object *object, u64 addr)
{
	struct nv04_instmem_priv *priv = (void *)object;
	return ioread32_native(priv->iomem + addr);
}