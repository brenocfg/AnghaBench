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
struct nv50_fifo_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_fifo_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv50_fifo_playlist_update (struct nv50_fifo_priv*) ; 
 int /*<<< orphan*/  nv_mask (struct nv50_fifo_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_fifo_priv*,int,int) ; 

int
nv50_fifo_init(struct nouveau_object *object)
{
	struct nv50_fifo_priv *priv = (void *)object;
	int ret, i;

	ret = nouveau_fifo_init(&priv->base);
	if (ret)
		return ret;

	nv_mask(priv, 0x000200, 0x00000100, 0x00000000);
	nv_mask(priv, 0x000200, 0x00000100, 0x00000100);
	nv_wr32(priv, 0x00250c, 0x6f3cfc34);
	nv_wr32(priv, 0x002044, 0x01003fff);

	nv_wr32(priv, 0x002100, 0xffffffff);
	nv_wr32(priv, 0x002140, 0xbfffffff);

	for (i = 0; i < 128; i++)
		nv_wr32(priv, 0x002600 + (i * 4), 0x00000000);
	nv50_fifo_playlist_update(priv);

	nv_wr32(priv, 0x003200, 0x00000001);
	nv_wr32(priv, 0x003250, 0x00000001);
	nv_wr32(priv, 0x002500, 0x00000001);
	return 0;
}