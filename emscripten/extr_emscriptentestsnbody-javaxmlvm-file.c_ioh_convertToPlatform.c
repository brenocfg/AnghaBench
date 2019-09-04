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
 char DIR_SEPARATOR ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

void ioh_convertToPlatform (char *path)
{
    char *pathIndex;
#if !(DIR_SEPARATOR == '/')
    size_t length = strlen (path);
#endif
    
    /* Convert all separators to the same type */
    pathIndex = path;
    while (*pathIndex != '\0')
    {
        if ((*pathIndex == '\\' || *pathIndex == '/')
            && (*pathIndex != DIR_SEPARATOR))
            *pathIndex = DIR_SEPARATOR;
        pathIndex++;
    }

#if !(DIR_SEPARATOR == '/')
    /* Remove duplicate initial separators */
    pathIndex = path;
    while ((*pathIndex != '\0') && (*pathIndex == DIR_SEPARATOR))
    {
        pathIndex++;
    }
    if ((pathIndex > path) && ((int)length > (pathIndex - path))
        && (*(pathIndex + 1) == ':'))
    {
        /* For Example '////c:/!*' (! added to avoid gcc warning) */
        size_t newlen = length - (pathIndex - path);
        memmove (path, pathIndex, newlen);
        path[newlen] = '\0';
    }
    else
    {
        if ((pathIndex - path > 3) && ((int)length > (pathIndex - path)))
        {
            /* For Example '////serverName/!*' (! added to avoid gcc warning) */
            size_t newlen = length - (pathIndex - path) + 2;
            memmove (path, pathIndex - 2, newlen);
            path[newlen] = '\0';
        }
    }
    /* This will have to handle extra \'s but currently doesn't */
#endif
    
}