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
struct nv50_instmem_priv {unsigned long long addr; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_instmem_fini (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nv50_instmem_fini(struct nouveau_object *object, bool suspend)
{
	struct nv50_instmem_priv *priv = (void *)object;
	priv->addr = ~0ULL;
	return nouveau_instmem_fini(&priv->base, suspend);
}