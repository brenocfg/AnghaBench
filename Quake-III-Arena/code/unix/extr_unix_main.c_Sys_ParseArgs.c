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
 int /*<<< orphan*/  Sys_Exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_PrintBinVersion (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void Sys_ParseArgs( int argc, char* argv[] ) {

  if ( argc==2 )
  {
    if ( (!strcmp( argv[1], "--version" ))
         || ( !strcmp( argv[1], "-v" )) )
    {
      Sys_PrintBinVersion( argv[0] );
      Sys_Exit(0);
    }
  }
}