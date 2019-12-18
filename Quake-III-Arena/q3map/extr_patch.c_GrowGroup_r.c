#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int byte ;

/* Variables and functions */

void GrowGroup_r( int patchNum, int patchCount, const byte *bordering, byte *group ) {
	int		i;
	const byte *row;

	if ( group[patchNum] ) {
		return;
	}
	group[patchNum] = 1;
	row = bordering + patchNum * patchCount;
	for ( i = 0 ; i < patchCount ; i++ ) {
		if ( row[i] ) {
			GrowGroup_r( i, patchCount, bordering, group );
		}
	}
}