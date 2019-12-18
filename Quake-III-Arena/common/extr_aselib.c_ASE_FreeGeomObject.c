#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numFrames; TYPE_1__* frames; } ;
struct TYPE_8__ {TYPE_2__ anim; } ;
typedef  TYPE_3__ aseGeomObject_t ;
struct TYPE_9__ {TYPE_3__* objects; } ;
struct TYPE_6__ {scalar_t__ tfaces; scalar_t__ faces; scalar_t__ tvertexes; scalar_t__ vertexes; } ;

/* Variables and functions */
 TYPE_5__ ase ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ASE_FreeGeomObject( int ndx )
{
	aseGeomObject_t *pObject;
	int i;

	pObject = &ase.objects[ndx];

	for ( i = 0; i < pObject->anim.numFrames; i++ )
	{
		if ( pObject->anim.frames[i].vertexes )
		{
			free( pObject->anim.frames[i].vertexes );
		}
		if ( pObject->anim.frames[i].tvertexes )
		{
			free( pObject->anim.frames[i].tvertexes );
		}
		if ( pObject->anim.frames[i].faces )
		{
			free( pObject->anim.frames[i].faces );
		}
		if ( pObject->anim.frames[i].tfaces )
		{
			free( pObject->anim.frames[i].tfaces );
		}
	}

	memset( pObject, 0, sizeof( *pObject ) );
}