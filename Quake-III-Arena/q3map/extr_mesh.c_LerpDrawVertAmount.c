#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float* xyz; float* st; float* lightmap; float* color; float* normal; } ;
typedef  TYPE_1__ drawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorNormalize (float*,float*) ; 

void LerpDrawVertAmount( drawVert_t *a, drawVert_t *b, float amount, drawVert_t *out ) {
	out->xyz[0] = a->xyz[0] + amount * (b->xyz[0] - a->xyz[0]);
	out->xyz[1] = a->xyz[1] + amount * (b->xyz[1] - a->xyz[1]);
	out->xyz[2] = a->xyz[2] + amount * (b->xyz[2] - a->xyz[2]);

	out->st[0] = a->st[0] + amount * (b->st[0] - a->st[0]);
	out->st[1] = a->st[1] + amount * (b->st[1] - a->st[1]);

	out->lightmap[0] = a->lightmap[0] + amount * (b->lightmap[0] - a->lightmap[0]);
	out->lightmap[1] = a->lightmap[1] + amount * (b->lightmap[1] - a->lightmap[1]);

	out->color[0] = a->color[0] + amount * (b->color[0] - a->color[0]);
	out->color[1] = a->color[1] + amount * (b->color[1] - a->color[1]);
	out->color[2] = a->color[2] + amount * (b->color[2] - a->color[2]);
	out->color[3] = a->color[3] + amount * (b->color[3] - a->color[3]);

	out->normal[0] = a->normal[0] + amount * (b->normal[0] - a->normal[0]);
	out->normal[1] = a->normal[1] + amount * (b->normal[1] - a->normal[1]);
	out->normal[2] = a->normal[2] + amount * (b->normal[2] - a->normal[2]);
	VectorNormalize(out->normal, out->normal);
}