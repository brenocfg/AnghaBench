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
struct TYPE_4__ {int contents; int surfaceFlags; int /*<<< orphan*/  shaderInfo; } ;
typedef  TYPE_1__ side_t ;
typedef  void* qboolean ;
struct TYPE_5__ {int numsides; int contents; void* opaque; void* detail; int /*<<< orphan*/  brushnum; int /*<<< orphan*/  entitynum; TYPE_1__* sides; int /*<<< orphan*/  contentShader; } ;
typedef  TYPE_2__ bspbrush_t ;

/* Variables and functions */
 int CONTENTS_AREAPORTAL ; 
 int CONTENTS_DETAIL ; 
 int CONTENTS_STRUCTURAL ; 
 int CONTENTS_TRANSLUCENT ; 
 int /*<<< orphan*/  _printf (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_areaportals ; 
 int /*<<< orphan*/  c_detail ; 
 int /*<<< orphan*/  c_structural ; 
 int /*<<< orphan*/  entitySourceBrushes ; 
 scalar_t__ fulldetail ; 
 scalar_t__ num_entities ; 
 void* qfalse ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* qtrue ; 

void SetBrushContents( bspbrush_t *b ) {
	int			contents, c2;
	side_t		*s;
	int			i;
	qboolean	mixed;
	int			allFlags;

	s = &b->sides[0];
	contents = s->contents;
	b->contentShader = s->shaderInfo;
	mixed = qfalse;

	allFlags = 0;

	for ( i=1 ; i<b->numsides ; i++, s++ ) {
		s = &b->sides[i];

		if ( !s->shaderInfo ) {
			continue;
		}

		c2 = s->contents;
		if (c2 != contents) {
			mixed = qtrue;
		}

		allFlags |= s->surfaceFlags;
	}

	if ( mixed ) {
		qprintf ("Entity %i, Brush %i: mixed face contents\n"
			, b->entitynum, b->brushnum);
	}

	if ( ( contents & CONTENTS_DETAIL ) && ( contents & CONTENTS_STRUCTURAL ) ) {
		_printf ("Entity %i, Brush %i: mixed CONTENTS_DETAIL and CONTENTS_STRUCTURAL\n"
			, num_entities-1, entitySourceBrushes );
		contents &= ~CONTENTS_DETAIL;
	}

	// the fulldetail flag will cause detail brushes to be
	// treated like normal brushes
	if ( fulldetail ) {
		contents &= ~CONTENTS_DETAIL;
	}

	// all translucent brushes that aren't specirically made structural will
	// be detail
	if ( ( contents & CONTENTS_TRANSLUCENT ) && !( contents & CONTENTS_STRUCTURAL ) ) {
		contents |= CONTENTS_DETAIL;
	}

	if ( contents & CONTENTS_DETAIL ) {
		c_detail++;
		b->detail = qtrue;
	} else {
		c_structural++;
		b->detail = qfalse;
	}

	if ( contents & CONTENTS_TRANSLUCENT ) {
		b->opaque = qfalse;
	} else {
		b->opaque = qtrue;
	}

	if ( contents & CONTENTS_AREAPORTAL ) {
		c_areaportals++;
	}

	b->contents = contents;
}