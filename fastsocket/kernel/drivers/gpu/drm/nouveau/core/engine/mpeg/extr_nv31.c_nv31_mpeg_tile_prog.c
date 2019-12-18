#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nv31_mpeg_priv {int dummy; } ;
struct nouveau_fb_tile {int /*<<< orphan*/  addr; int /*<<< orphan*/  limit; int /*<<< orphan*/  pitch; } ;
struct nouveau_engine {int dummy; } ;
struct TYPE_3__ {struct nouveau_fb_tile* region; } ;
struct TYPE_4__ {TYPE_1__ tile; } ;

/* Variables and functions */
 TYPE_2__* nouveau_fb (struct nouveau_engine*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv31_mpeg_priv*,int,int /*<<< orphan*/ ) ; 

void
nv31_mpeg_tile_prog(struct nouveau_engine *engine, int i)
{
	struct nouveau_fb_tile *tile = &nouveau_fb(engine)->tile.region[i];
	struct nv31_mpeg_priv *priv = (void *)engine;

	nv_wr32(priv, 0x00b008 + (i * 0x10), tile->pitch);
	nv_wr32(priv, 0x00b004 + (i * 0x10), tile->limit);
	nv_wr32(priv, 0x00b000 + (i * 0x10), tile->addr);
}