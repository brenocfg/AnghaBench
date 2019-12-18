#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Org; } ;
struct TYPE_9__ {int /*<<< orphan*/  env; int /*<<< orphan*/  mesh; } ;
typedef  TYPE_1__ TESStesselator ;
typedef  double TESSreal ;
typedef  TYPE_2__ TESShalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  CallCombine (TYPE_1__*,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tessMeshSplice (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void SpliceMergeVertices( TESStesselator *tess, TESShalfEdge *e1,
								TESShalfEdge *e2 )
/*
* Two vertices with idential coordinates are combined into one.
* e1->Org is kept, while e2->Org is discarded.
*/
{
	TESSreal weights[4] = { 0.5, 0.5, 0.0, 0.0 };

	CallCombine( tess, e1->Org, weights, FALSE );
	if ( !tessMeshSplice( tess->mesh, e1, e2 ) ) longjmp(tess->env,1); 
}