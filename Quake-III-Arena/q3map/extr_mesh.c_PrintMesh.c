#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int height; int width; TYPE_1__* verts; } ;
typedef  TYPE_2__ mesh_t ;
struct TYPE_4__ {int /*<<< orphan*/ * xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  _printf (char*,...) ; 

void PrintMesh( mesh_t *m ) {
	int		i, j;

	for ( i = 0 ; i < m->height ; i++ ) {
		for ( j = 0 ; j < m->width ; j++ ) {
			_printf("(%5.2f %5.2f %5.2f) "
				, m->verts[i*m->width+j].xyz[0]
				, m->verts[i*m->width+j].xyz[1]
				, m->verts[i*m->width+j].xyz[2] );
		}
		_printf("\n");
	}
}