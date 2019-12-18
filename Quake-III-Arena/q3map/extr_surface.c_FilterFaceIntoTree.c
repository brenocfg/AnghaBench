#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_8__ {int /*<<< orphan*/  side; } ;
typedef  TYPE_2__ mapDrawSurface_t ;

/* Variables and functions */
 int FilterSideIntoTree_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WindingFromDrawSurf (TYPE_2__*) ; 

int	FilterFaceIntoTree( mapDrawSurface_t *ds, tree_t *tree ) {
	int			l;
	winding_t	*w;

	w = WindingFromDrawSurf( ds );
	l = FilterSideIntoTree_r( w, ds->side, ds, tree->headnode );

	return l;
}