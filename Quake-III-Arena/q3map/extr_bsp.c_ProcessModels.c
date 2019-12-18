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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int /*<<< orphan*/  patches; int /*<<< orphan*/  brushes; } ;
typedef  TYPE_1__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  BeginBSPFile () ; 
 int /*<<< orphan*/  ProcessSubModel () ; 
 int /*<<< orphan*/  ProcessWorldModel () ; 
 TYPE_1__* entities ; 
 size_t entity_num ; 
 size_t num_entities ; 
 int /*<<< orphan*/  nummodels ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  verboseentities ; 

void ProcessModels (void)
{
	qboolean	oldVerbose;
	entity_t	*entity;

	oldVerbose = verbose;

	BeginBSPFile ();

	for ( entity_num=0 ; entity_num< num_entities ; entity_num++ ) {
		entity = &entities[entity_num];
	
		if ( !entity->brushes && !entity->patches ) {
			continue;
		}

		qprintf ("############### model %i ###############\n", nummodels);
		if (entity_num == 0)
			ProcessWorldModel ();
		else
			ProcessSubModel ();

		if (!verboseentities)
			verbose = qfalse;	// don't bother printing submodels
	}

	verbose = oldVerbose;
}