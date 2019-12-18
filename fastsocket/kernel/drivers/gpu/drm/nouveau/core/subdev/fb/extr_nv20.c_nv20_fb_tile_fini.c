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
struct nouveau_fb_tile {int /*<<< orphan*/  tag; scalar_t__ zcomp; scalar_t__ pitch; scalar_t__ limit; scalar_t__ addr; } ;
struct nouveau_fb {int /*<<< orphan*/  tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_mm_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nv20_fb_tile_fini(struct nouveau_fb *pfb, int i, struct nouveau_fb_tile *tile)
{
	tile->addr  = 0;
	tile->limit = 0;
	tile->pitch = 0;
	tile->zcomp = 0;
	nouveau_mm_free(&pfb->tags, &tile->tag);
}