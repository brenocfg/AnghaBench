#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  terrainVert_t ;
struct TYPE_3__ {int width; int /*<<< orphan*/ * map; } ;
typedef  TYPE_1__ terrainMesh_t ;

/* Variables and functions */

terrainVert_t *Terrain_GetVert( terrainMesh_t *pm, int x, int y ) {
	return &pm->map[ x + y * pm->width ];
}