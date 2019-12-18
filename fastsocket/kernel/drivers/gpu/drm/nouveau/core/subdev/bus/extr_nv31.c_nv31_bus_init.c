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
struct nv31_bus_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_bus_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv31_bus_priv*,int,int) ; 

__attribute__((used)) static int
nv31_bus_init(struct nouveau_object *object)
{
	struct nv31_bus_priv *priv = (void *)object;
	int ret;

	ret = nouveau_bus_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x001100, 0xffffffff);
	nv_wr32(priv, 0x001140, 0x00070008);
	return 0;
}