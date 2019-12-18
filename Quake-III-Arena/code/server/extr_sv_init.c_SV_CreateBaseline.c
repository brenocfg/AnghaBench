#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int number; } ;
struct TYPE_7__ {int /*<<< orphan*/  linked; } ;
struct TYPE_10__ {TYPE_3__ s; TYPE_1__ r; } ;
typedef  TYPE_4__ sharedEntity_t ;
struct TYPE_11__ {int num_entities; TYPE_2__* svEntities; } ;
struct TYPE_8__ {TYPE_3__ baseline; } ;

/* Variables and functions */
 TYPE_4__* SV_GentityNum (int) ; 
 TYPE_5__ sv ; 

void SV_CreateBaseline( void ) {
	sharedEntity_t *svent;
	int				entnum;	

	for ( entnum = 1; entnum < sv.num_entities ; entnum++ ) {
		svent = SV_GentityNum(entnum);
		if (!svent->r.linked) {
			continue;
		}
		svent->s.number = entnum;

		//
		// take current state as baseline
		//
		sv.svEntities[entnum].baseline = svent->s;
	}
}