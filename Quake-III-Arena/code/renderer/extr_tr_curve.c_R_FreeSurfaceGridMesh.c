#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* heightLodError; struct TYPE_7__* widthLodError; } ;
typedef  TYPE_1__ srfGridMesh_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* Free ) (TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_5__ ri ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

void R_FreeSurfaceGridMesh( srfGridMesh_t *grid ) {
	ri.Free(grid->widthLodError);
	ri.Free(grid->heightLodError);
	ri.Free(grid);
}