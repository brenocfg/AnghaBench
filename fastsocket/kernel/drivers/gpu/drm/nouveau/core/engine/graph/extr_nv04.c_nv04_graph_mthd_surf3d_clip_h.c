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
struct nv04_graph_priv {int dummy; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nv04_graph_priv*,int,int) ; 

__attribute__((used)) static int
nv04_graph_mthd_surf3d_clip_h(struct nouveau_object *object, u32 mthd,
			      void *args, u32 size)
{
	struct nv04_graph_priv *priv = (void *)object->engine;
	u32 data = *(u32 *)args;
	u32 min = data & 0xffff, max;
	u32 w = data >> 16;
	if (min & 0x8000)
		/* too large */
		return 1;
	if (w & 0x8000)
		/* yes, it accepts negative for some reason. */
		w |= 0xffff0000;
	max = min + w;
	max &= 0x3ffff;
	nv_wr32(priv, 0x40053c, min);
	nv_wr32(priv, 0x400544, max);
	return 0;
}