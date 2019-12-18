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
struct nouveau_fb_tile {int addr; int pitch; scalar_t__ limit; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* comp ) (struct nouveau_fb*,int,int,int,struct nouveau_fb_tile*) ;} ;
struct nouveau_fb {TYPE_1__ tile; } ;

/* Variables and functions */
 scalar_t__ max (unsigned int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fb*,int,int,int,struct nouveau_fb_tile*) ; 

void
nv30_fb_tile_init(struct nouveau_fb *pfb, int i, u32 addr, u32 size, u32 pitch,
		  u32 flags, struct nouveau_fb_tile *tile)
{
	/* for performance, select alternate bank offset for zeta */
	if (!(flags & 4)) {
		tile->addr = (0 << 4);
	} else {
		if (pfb->tile.comp) /* z compression */
			pfb->tile.comp(pfb, i, size, flags, tile);
		tile->addr = (1 << 4);
	}

	tile->addr |= 0x00000001; /* enable */
	tile->addr |= addr;
	tile->limit = max(1u, addr + size) - 1;
	tile->pitch = pitch;
}