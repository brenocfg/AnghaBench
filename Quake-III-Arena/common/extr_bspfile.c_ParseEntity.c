#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_6__ {TYPE_1__* epairs; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 size_t MAX_MAP_ENTITIES ; 
 TYPE_1__* ParseEpair () ; 
 TYPE_2__* entities ; 
 size_t num_entities ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  token ; 

qboolean	ParseEntity( void ) {
	epair_t		*e;
	entity_t	*mapent;

	if ( !GetToken (qtrue) ) {
		return qfalse;
	}

	if ( strcmp (token, "{") ) {
		Error ("ParseEntity: { not found");
	}
	if ( num_entities == MAX_MAP_ENTITIES ) {
		Error ("num_entities == MAX_MAP_ENTITIES");
	}
	mapent = &entities[num_entities];
	num_entities++;

	do {
		if ( !GetToken (qtrue) ) {
			Error ("ParseEntity: EOF without closing brace");
		}
		if ( !strcmp (token, "}") ) {
			break;
		}
		e = ParseEpair ();
		e->next = mapent->epairs;
		mapent->epairs = e;
	} while (1);
	
	return qtrue;
}