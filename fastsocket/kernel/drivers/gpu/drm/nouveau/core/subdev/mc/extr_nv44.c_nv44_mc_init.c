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
struct nv44_mc_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_mc_init (int /*<<< orphan*/ *) ; 
 int nv_rd32 (struct nv44_mc_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv44_mc_priv*,int,int) ; 

__attribute__((used)) static int
nv44_mc_init(struct nouveau_object *object)
{
	struct nv44_mc_priv *priv = (void *)object;
	u32 tmp = nv_rd32(priv, 0x10020c);

	nv_wr32(priv, 0x000200, 0xffffffff); /* everything enabled */

	nv_wr32(priv, 0x001700, tmp);
	nv_wr32(priv, 0x001704, 0);
	nv_wr32(priv, 0x001708, 0);
	nv_wr32(priv, 0x00170c, tmp);

	return nouveau_mc_init(&priv->base);
}