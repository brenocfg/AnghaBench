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
struct nv04_graph_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV03_PGRAPH_INTR ; 
 int /*<<< orphan*/  NV03_PGRAPH_INTR_EN ; 
 int /*<<< orphan*/  NV04_PGRAPH_BETA_AND ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_CONTROL ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_USER ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_0 ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_1 ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_2 ; 
 int /*<<< orphan*/  NV04_PGRAPH_DEBUG_3 ; 
 int /*<<< orphan*/  NV04_PGRAPH_PATTERN_SHAPE ; 
 int /*<<< orphan*/  NV04_PGRAPH_STATE ; 
 int /*<<< orphan*/  NV04_PGRAPH_VALID1 ; 
 int /*<<< orphan*/  NV04_PGRAPH_VALID2 ; 
 int nouveau_graph_init (int /*<<< orphan*/ *) ; 
 struct nouveau_engine* nv_engine (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_mask (struct nv04_graph_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_graph_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv04_graph_init(struct nouveau_object *object)
{
	struct nouveau_engine *engine = nv_engine(object);
	struct nv04_graph_priv *priv = (void *)engine;
	int ret;

	ret = nouveau_graph_init(&priv->base);
	if (ret)
		return ret;

	/* Enable PGRAPH interrupts */
	nv_wr32(priv, NV03_PGRAPH_INTR, 0xFFFFFFFF);
	nv_wr32(priv, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nv_wr32(priv, NV04_PGRAPH_VALID1, 0);
	nv_wr32(priv, NV04_PGRAPH_VALID2, 0);
	/*nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0x000001FF);
	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0x001FFFFF);*/
	nv_wr32(priv, NV04_PGRAPH_DEBUG_0, 0x1231c000);
	/*1231C000 blob, 001 haiku*/
	/*V_WRITE(NV04_PGRAPH_DEBUG_1, 0xf2d91100);*/
	nv_wr32(priv, NV04_PGRAPH_DEBUG_1, 0x72111100);
	/*0x72111100 blob , 01 haiku*/
	/*nv_wr32(priv, NV04_PGRAPH_DEBUG_2, 0x11d5f870);*/
	nv_wr32(priv, NV04_PGRAPH_DEBUG_2, 0x11d5f071);
	/*haiku same*/

	/*nv_wr32(priv, NV04_PGRAPH_DEBUG_3, 0xfad4ff31);*/
	nv_wr32(priv, NV04_PGRAPH_DEBUG_3, 0xf0d4ff31);
	/*haiku and blob 10d4*/

	nv_wr32(priv, NV04_PGRAPH_STATE        , 0xFFFFFFFF);
	nv_wr32(priv, NV04_PGRAPH_CTX_CONTROL  , 0x10000100);
	nv_mask(priv, NV04_PGRAPH_CTX_USER, 0xff000000, 0x0f000000);

	/* These don't belong here, they're part of a per-channel context */
	nv_wr32(priv, NV04_PGRAPH_PATTERN_SHAPE, 0x00000000);
	nv_wr32(priv, NV04_PGRAPH_BETA_AND     , 0xFFFFFFFF);
	return 0;
}