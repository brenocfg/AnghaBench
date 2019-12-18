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
typedef  int /*<<< orphan*/  u32 ;
struct nv04_graph_priv {int dummy; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 scalar_t__ NV04_PGRAPH_CTX_CACHE1 ; 
 scalar_t__ NV04_PGRAPH_CTX_SWITCH1 ; 
 int /*<<< orphan*/  NV04_PGRAPH_TRAPPED_ADDR ; 
 int nv_rd32 (struct nv04_graph_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_ro32 (struct nouveau_object*,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_object*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_graph_priv*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv04_graph_set_ctx1(struct nouveau_object *object, u32 mask, u32 value)
{
	struct nv04_graph_priv *priv = (void *)object->engine;
	int subc = (nv_rd32(priv, NV04_PGRAPH_TRAPPED_ADDR) >> 13) & 0x7;
	u32 tmp;

	tmp  = nv_ro32(object, 0x00);
	tmp &= ~mask;
	tmp |= value;
	nv_wo32(object, 0x00, tmp);

	nv_wr32(priv, NV04_PGRAPH_CTX_SWITCH1, tmp);
	nv_wr32(priv, NV04_PGRAPH_CTX_CACHE1 + (subc<<2), tmp);
}