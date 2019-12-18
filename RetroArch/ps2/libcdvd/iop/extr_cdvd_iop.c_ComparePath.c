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
typedef  enum PathMatch { ____Placeholder_PathMatch } PathMatch ;
struct TYPE_2__ {char const* pathname; } ;

/* Variables and functions */
 TYPE_1__ CachedDirInfo ; 
 int MATCH ; 
 int NOT_MATCH ; 
 int SUBDIR ; 
 int strlen (char const*) ; 

enum PathMatch ComparePath(const char *path)
{
    int length;
    int i;

    length = strlen(CachedDirInfo.pathname);

    for (i = 0; i < length; i++) {
        // check if character matches
        if (path[i] != CachedDirInfo.pathname[i]) {
            // if not, then is it just because of different path seperator ?
            if ((path[i] == '/') || (path[i] == '\\')) {
                if ((CachedDirInfo.pathname[i] == '/') || (CachedDirInfo.pathname[i] == '\\')) {
                    continue;
                }
            }

            // if the characters don't match for any other reason then report a failure
            return NOT_MATCH;
        }
    }

    // Reached the end of the Cached pathname

    // if requested path is same length, then report exact match
    if (path[length] == 0)
        return MATCH;

    // if requested path is longer, and next char is a dir seperator
    // then report sub-dir match
    if ((path[length] == '/') || (path[length] == '\\'))
        return SUBDIR;
    else
        return NOT_MATCH;
}