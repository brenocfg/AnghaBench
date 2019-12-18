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
struct nouveau_fb_tile {int /*<<< orphan*/  zcomp; int /*<<< orphan*/  addr; int /*<<< orphan*/  pitch; int /*<<< orphan*/  limit; } ;
struct nouveau_fb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_rd32 (struct nouveau_fb*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_fb*,int,int /*<<< orphan*/ ) ; 

void
nv41_fb_tile_prog(struct nouveau_fb *pfb, int i, struct nouveau_fb_tile *tile)
{
	nv_wr32(pfb, 0x100604 + (i * 0x10), tile->limit);
	nv_wr32(pfb, 0x100608 + (i * 0x10), tile->pitch);
	nv_wr32(pfb, 0x100600 + (i * 0x10), tile->addr);
	nv_rd32(pfb, 0x100600 + (i * 0x10));
	nv_wr32(pfb, 0x100700 + (i * 0x04), tile->zcomp);
}