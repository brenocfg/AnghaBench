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
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_3__ {scalar_t__ firstBrush; scalar_t__ numBrushes; scalar_t__ firstSurface; scalar_t__ numSurfaces; } ;
typedef  TYPE_1__ dmodel_t ;

/* Variables and functions */
 int /*<<< orphan*/  EmitDrawNode_r (int /*<<< orphan*/ *) ; 
 TYPE_1__* dmodels ; 
 scalar_t__ numDrawSurfaces ; 
 scalar_t__ numbrushes ; 
 size_t nummodels ; 
 int /*<<< orphan*/  qprintf (char*) ; 

void EndModel( node_t *headnode ) {
	dmodel_t	*mod;

	qprintf ("--- EndModel ---\n");

	mod = &dmodels[nummodels];
	EmitDrawNode_r (headnode);
	mod->numSurfaces = numDrawSurfaces - mod->firstSurface;
	mod->numBrushes = numbrushes - mod->firstBrush;

	nummodels++;
}