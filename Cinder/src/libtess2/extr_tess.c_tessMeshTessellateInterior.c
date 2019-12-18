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
struct TYPE_7__ {scalar_t__ inside; struct TYPE_7__* next; } ;
struct TYPE_6__ {TYPE_2__ fHead; } ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESSface ;

/* Variables and functions */
 int /*<<< orphan*/  tessMeshTessellateMonoRegion (TYPE_1__*,TYPE_2__*) ; 

int tessMeshTessellateInterior( TESSmesh *mesh )
{
	TESSface *f, *next;

	/*LINTED*/
	for( f = mesh->fHead.next; f != &mesh->fHead; f = next ) {
		/* Make sure we don''t try to tessellate the new triangles. */
		next = f->next;
		if( f->inside ) {
			if ( !tessMeshTessellateMonoRegion( mesh, f ) ) return 0;
		}
	}

	return 1;
}