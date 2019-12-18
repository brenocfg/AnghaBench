#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__** bounds; } ;
typedef  TYPE_3__ fog_t ;
struct TYPE_11__ {scalar_t__* origin; int /*<<< orphan*/  color; } ;
typedef  TYPE_4__ dlight_t ;
struct TYPE_8__ {int num_dlights; TYPE_4__* dlights; } ;
struct TYPE_14__ {TYPE_1__ refdef; } ;
struct TYPE_13__ {int /*<<< orphan*/  integer; } ;
struct TYPE_12__ {TYPE_2__* world; } ;
struct TYPE_9__ {int numfogs; TYPE_3__* fogs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_AddFlare (void*,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_7__ backEnd ; 
 TYPE_6__* r_flares ; 
 TYPE_5__ tr ; 

void RB_AddDlightFlares( void ) {
	dlight_t		*l;
	int				i, j, k;
	fog_t			*fog;

	if ( !r_flares->integer ) {
		return;
	}

	l = backEnd.refdef.dlights;
	fog = tr.world->fogs;
	for (i=0 ; i<backEnd.refdef.num_dlights ; i++, l++) {

		// find which fog volume the light is in 
		for ( j = 1 ; j < tr.world->numfogs ; j++ ) {
			fog = &tr.world->fogs[j];
			for ( k = 0 ; k < 3 ; k++ ) {
				if ( l->origin[k] < fog->bounds[0][k] || l->origin[k] > fog->bounds[1][k] ) {
					break;
				}
			}
			if ( k == 3 ) {
				break;
			}
		}
		if ( j == tr.world->numfogs ) {
			j = 0;
		}

		RB_AddFlare( (void *)l, j, l->origin, l->color, NULL );
	}
}