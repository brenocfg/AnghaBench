#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ parseMesh_t ;
struct TYPE_7__ {TYPE_1__* patches; TYPE_3__* brushes; } ;
typedef  TYPE_2__ entity_t ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_3__ bspbrush_t ;
struct TYPE_9__ {TYPE_1__* patches; TYPE_3__* brushes; } ;

/* Variables and functions */
 TYPE_4__* entities ; 

void MoveBrushesToWorld (entity_t *mapent) {
	bspbrush_t	*b, *next;
	parseMesh_t	*pm;

	// move brushes
	for ( b = mapent->brushes ; b ; b = next ) {
		next = b->next;

		b->next = entities[0].brushes;
		entities[0].brushes = b;
	}
	mapent->brushes = NULL;

	// move patches
	if ( mapent->patches ) {

		for ( pm = mapent->patches ; pm->next ; pm = pm->next ) {
		}

		pm->next = entities[0].patches;
		entities[0].patches = mapent->patches;

		mapent->patches = NULL;
	}
}