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
struct TYPE_3__ {int width; int height; int /*<<< orphan*/ ** points; } ;
typedef  TYPE_1__ cGrid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ComparePoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CM_RemoveDegenerateColumns( cGrid_t *grid ) {
	int		i, j, k;

	for ( i = 0 ; i < grid->width - 1 ; i++ ) {
		for ( j = 0 ; j < grid->height ; j++ ) {
			if ( !CM_ComparePoints( grid->points[i][j], grid->points[i+1][j] ) ) {
				break;
			}
		}

		if ( j != grid->height ) {
			continue;	// not degenerate
		}

		for ( j = 0 ; j < grid->height ; j++ ) {
			// remove the column
			for ( k = i + 2 ; k < grid->width ; k++ ) {
				VectorCopy( grid->points[k][j], grid->points[k-1][j] );
			}
		}
		grid->width--;

		// check against the next column
		i--;
	}
}