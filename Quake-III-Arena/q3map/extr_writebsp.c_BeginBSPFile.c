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
 scalar_t__ numbrushsides ; 
 scalar_t__ numleafbrushes ; 
 int numleafs ; 
 scalar_t__ numleafsurfaces ; 
 scalar_t__ nummodels ; 
 scalar_t__ numnodes ; 

void BeginBSPFile( void ) {
	// these values may actually be initialized
	// if the file existed when loaded, so clear them explicitly
	nummodels = 0;
	numnodes = 0;
	numbrushsides = 0;
	numleafsurfaces = 0;
	numleafbrushes = 0;

	// leave leaf 0 as an error, because leafs are referenced as
	// negative number nodes
	numleafs = 1;
}