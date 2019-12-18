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
struct nv50_disp_priv {int dummy; } ;
struct nv50_disp_chan {int chid; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nv50_disp_priv*,scalar_t__,int /*<<< orphan*/ ) ; 

void
nv50_disp_chan_wr32(struct nouveau_object *object, u64 addr, u32 data)
{
	struct nv50_disp_priv *priv = (void *)object->engine;
	struct nv50_disp_chan *chan = (void *)object;
	nv_wr32(priv, 0x640000 + (chan->chid * 0x1000) + addr, data);
}