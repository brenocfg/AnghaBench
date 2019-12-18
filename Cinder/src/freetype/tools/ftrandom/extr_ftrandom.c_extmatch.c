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
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
  extmatch( char*   filename,
            char**  extensions )
  {
    int    i;
    char*  pt;


    if ( !extensions )
      return true;

    pt = strrchr( filename, '.' );
    if ( !pt )
      return false;
    if ( pt < strrchr( filename, '/' ) )
      return false;

    for ( i = 0; extensions[i] != NULL; i++ )
      if ( strcasecmp( pt + 1, extensions[i] ) == 0 ||
           strcasecmp( pt,     extensions[i] ) == 0 )
        return true;

    return false;
  }