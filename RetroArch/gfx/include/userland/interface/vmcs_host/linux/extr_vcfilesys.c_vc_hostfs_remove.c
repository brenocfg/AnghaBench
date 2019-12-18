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
 int /*<<< orphan*/  DEBUG_MINOR (char*,char const*) ; 
 int /*<<< orphan*/  backslash_to_slash (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ unlink (char*) ; 

int vc_hostfs_remove(const char *path)
{
    char *pathbuf = strdup(path);
    int ret = -1;

    DEBUG_MINOR( "vc_hostfs_remove: '%s'", path );

    if (pathbuf)
    {
       backslash_to_slash(pathbuf);

       if ( unlink( pathbuf ) == 0 )
          ret = 0;
    }

    free(pathbuf);

    return ret;
}