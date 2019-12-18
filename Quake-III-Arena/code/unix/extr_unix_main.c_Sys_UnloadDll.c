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
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 char* dlerror () ; 

void Sys_UnloadDll( void *dllHandle ) {
  // bk001206 - verbose error reporting
  const char* err; // rb010123 - now const
  if ( !dllHandle )
  {
    Com_Printf("Sys_UnloadDll(NULL)\n");
    return;
  }
  dlclose( dllHandle );
  err = dlerror();
  if ( err != NULL )
    Com_Printf ( "Sys_UnloadGame failed on dlclose: \"%s\"!\n", err );
}