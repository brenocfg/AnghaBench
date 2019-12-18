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
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  LoadBSPFile (char*) ; 
 int /*<<< orphan*/  LoadMapFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBSPFile (char*) ; 
 int /*<<< orphan*/  name ; 
 int numDrawSurfaces ; 
 char* source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void OnlyTextures( void ) {		// FIXME!!!
	char	out[1024];
	int		i;

	Error( "-onlytextures isn't working now..." );

	sprintf (out, "%s.bsp", source);

	LoadMapFile (name);

	LoadBSPFile (out);

	// replace all the drawsurface shader names
	for ( i = 0 ; i < numDrawSurfaces ; i++ ) {
	}

	WriteBSPFile (out);
}