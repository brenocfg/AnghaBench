#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_7__ {int /*<<< orphan*/  lightmapOrigin; } ;
typedef  TYPE_2__ mapDrawSurface_t ;

/* Variables and functions */
 int FilterMapDrawSurfIntoTree (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

int	FilterFlareSurfIntoTree( mapDrawSurface_t *ds, tree_t *tree ) {
	return FilterMapDrawSurfIntoTree( ds->lightmapOrigin, ds, tree->headnode );
}