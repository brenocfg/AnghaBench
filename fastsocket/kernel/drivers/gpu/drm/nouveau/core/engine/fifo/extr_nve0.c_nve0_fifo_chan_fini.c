#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nve0_fifo_priv {int dummy; } ;
struct TYPE_2__ {int chid; } ;
struct nve0_fifo_chan {TYPE_1__ base; int /*<<< orphan*/  engine; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int nouveau_fifo_channel_fini (TYPE_1__*,int) ; 
 int /*<<< orphan*/  nv_mask (struct nve0_fifo_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nve0_fifo_priv*,int,int) ; 
 int /*<<< orphan*/  nve0_fifo_playlist_update (struct nve0_fifo_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nve0_fifo_chan_fini(struct nouveau_object *object, bool suspend)
{
	struct nve0_fifo_priv *priv = (void *)object->engine;
	struct nve0_fifo_chan *chan = (void *)object;
	u32 chid = chan->base.chid;

	nv_mask(priv, 0x800004 + (chid * 8), 0x00000800, 0x00000800);
	nve0_fifo_playlist_update(priv, chan->engine);
	nv_wr32(priv, 0x800000 + (chid * 8), 0x00000000);

	return nouveau_fifo_channel_fini(&chan->base, suspend);
}