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
struct TYPE_4__ {int planenum; } ;
typedef  TYPE_1__ side_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int numsides; int /*<<< orphan*/  brushnum; int /*<<< orphan*/  entitynum; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  _printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean RemoveDuplicateBrushPlanes( bspbrush_t * b ) {
	int			i, j, k;
	side_t		*sides;

	sides = b->sides;

	for ( i = 1 ; i < b->numsides ; i++ ) {

		// check for a degenerate plane
		if ( sides[i].planenum == -1) {
			_printf ("Entity %i, Brush %i: degenerate plane\n"
				, b->entitynum, b->brushnum);
			// remove it
			for ( k = i + 1 ; k < b->numsides ; k++ ) {
				sides[k-1] = sides[k];
			}
			b->numsides--;
			i--;
			continue;
		}

		// check for duplication and mirroring
		for ( j = 0 ; j < i ; j++ ) {
			if ( sides[i].planenum == sides[j].planenum ) {
				_printf ("Entity %i, Brush %i: duplicate plane\n"
					, b->entitynum, b->brushnum);
				// remove the second duplicate
				for ( k = i + 1 ; k < b->numsides ; k++ ) {
					sides[k-1] = sides[k];
				}
				b->numsides--;
				i--;
				break;
			}

			if ( sides[i].planenum == (sides[j].planenum ^ 1) ) {
				// mirror plane, brush is invalid
				_printf ("Entity %i, Brush %i: mirrored plane\n"
					, b->entitynum, b->brushnum);
				return qfalse;
			}
		}
	}
	return qtrue;
}