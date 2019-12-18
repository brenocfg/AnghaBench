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
 int /*<<< orphan*/  EmitPlanes () ; 
 int /*<<< orphan*/  UnparseEntities () ; 
 int /*<<< orphan*/  WriteBSPFile (char*) ; 
 int /*<<< orphan*/  _printf (char*,char*) ; 
 char* source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void EndBSPFile( void ) {
	char	path[1024];

	EmitPlanes ();
	UnparseEntities ();

	// write the map
	sprintf (path, "%s.bsp", source);
	_printf ("Writing %s\n", path);
	WriteBSPFile (path);
}