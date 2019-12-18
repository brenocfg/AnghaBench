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

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int,scalar_t__) ; 
 scalar_t__* pcount ; 

void MSG_ReportChangeVectors_f( void ) {
	int i;
	for(i=0;i<256;i++) {
		if (pcount[i]) {
			Com_Printf("%d used %d\n", i, pcount[i]);
		}
	}
}