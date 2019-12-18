#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bspbrush_t ;
struct TYPE_5__ {int* portalareas; int contents; int /*<<< orphan*/  brushnum; scalar_t__ entitynum; } ;

/* Variables and functions */
 int CONTENTS_DETAIL ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/ * FinishBrush () ; 
 int /*<<< orphan*/  FreeBrush (TYPE_1__*) ; 
 int /*<<< orphan*/  ParseRawBrush () ; 
 int /*<<< orphan*/  RemoveDuplicateBrushPlanes (TYPE_1__*) ; 
 int /*<<< orphan*/  SetBrushContents (TYPE_1__*) ; 
 TYPE_1__* buildBrush ; 
 int /*<<< orphan*/  entitySourceBrushes ; 
 scalar_t__ nodetail ; 
 scalar_t__ nowater ; 
 scalar_t__ num_entities ; 

void ParseBrush (void) {
	bspbrush_t	*b;

	ParseRawBrush();

	buildBrush->portalareas[0] = -1;
	buildBrush->portalareas[1] = -1;
	buildBrush->entitynum = num_entities-1;
	buildBrush->brushnum = entitySourceBrushes;

	// if there are mirrored planes, the entire brush is invalid
	if ( !RemoveDuplicateBrushPlanes( buildBrush ) ) {
		return;
	}

	// get the content for the entire brush
	SetBrushContents( buildBrush );

	// allow detail brushes to be removed 
	if (nodetail && (buildBrush->contents & CONTENTS_DETAIL) ) {
		FreeBrush( buildBrush );
		return;
	}

	// allow water brushes to be removed
	if (nowater && (buildBrush->contents & (CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER)) ) {
		FreeBrush( buildBrush );
		return;
	}

	b = FinishBrush( );
	if ( !b ) {
		return;
	}
}