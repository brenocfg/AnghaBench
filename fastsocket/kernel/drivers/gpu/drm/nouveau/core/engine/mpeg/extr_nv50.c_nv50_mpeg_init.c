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
struct nv50_mpeg_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int nouveau_mpeg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_error (struct nv50_mpeg_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_mask (struct nv50_mpeg_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_rd32 (struct nv50_mpeg_priv*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nv50_mpeg_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_mpeg_priv*,int,int) ; 

int
nv50_mpeg_init(struct nouveau_object *object)
{
	struct nv50_mpeg_priv *priv = (void *)object;
	int ret;

	ret = nouveau_mpeg_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x00b32c, 0x00000000);
	nv_wr32(priv, 0x00b314, 0x00000100);
	nv_wr32(priv, 0x00b0e0, 0x0000001a);

	nv_wr32(priv, 0x00b220, 0x00000044);
	nv_wr32(priv, 0x00b300, 0x00801ec1);
	nv_wr32(priv, 0x00b390, 0x00000000);
	nv_wr32(priv, 0x00b394, 0x00000000);
	nv_wr32(priv, 0x00b398, 0x00000000);
	nv_mask(priv, 0x00b32c, 0x00000001, 0x00000001);

	nv_wr32(priv, 0x00b100, 0xffffffff);
	nv_wr32(priv, 0x00b140, 0xffffffff);

	if (!nv_wait(priv, 0x00b200, 0x00000001, 0x00000000)) {
		nv_error(priv, "timeout 0x%08x\n", nv_rd32(priv, 0x00b200));
		return -EBUSY;
	}

	return 0;
}