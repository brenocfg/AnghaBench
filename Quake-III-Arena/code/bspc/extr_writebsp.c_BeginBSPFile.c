#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENTS_SOLID ; 
 TYPE_1__* dleafs ; 
 scalar_t__ numbrushsides ; 
 int numedges ; 
 scalar_t__ numfaces ; 
 scalar_t__ numleafbrushes ; 
 scalar_t__ numleaffaces ; 
 int numleafs ; 
 scalar_t__ nummodels ; 
 scalar_t__ numnodes ; 
 scalar_t__ numsurfedges ; 
 int numvertexes ; 

void BeginBSPFile (void)
{
	// these values may actually be initialized
	// if the file existed when loaded, so clear them explicitly
	nummodels = 0;
	numfaces = 0;
	numnodes = 0;
	numbrushsides = 0;
	numvertexes = 0;
	numleaffaces = 0;
	numleafbrushes = 0;
	numsurfedges = 0;

	// edge 0 is not used, because 0 can't be negated
	numedges = 1;

	// leave vertex 0 as an error
	numvertexes = 1;

	// leave leaf 0 as an error
	numleafs = 1;
	dleafs[0].contents = CONTENTS_SOLID;
}