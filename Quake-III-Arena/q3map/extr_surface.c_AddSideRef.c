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
struct TYPE_4__ {scalar_t__ planenum; scalar_t__ shaderInfo; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_5__ {scalar_t__ planenum; scalar_t__ shaderInfo; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_SIDE_REFS ; 
 int numSideRefs ; 
 TYPE_2__* sideRefs ; 

void AddSideRef( side_t *side ) {
	int		i;

	for ( i = 0 ; i < numSideRefs ; i++ ) {
		if ( side->planenum == sideRefs[i].planenum
			&& side->shaderInfo == sideRefs[i].shaderInfo ) {
			sideRefs[i].count++;
			return;
		}
	}

	if ( numSideRefs == MAX_SIDE_REFS ) {
		Error( "MAX_SIDE_REFS" );
	}

	sideRefs[i].planenum = side->planenum;
	sideRefs[i].shaderInfo = side->shaderInfo;
	sideRefs[i].count++;
	numSideRefs++;
}