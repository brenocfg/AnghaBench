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
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static const char * arg_extension(const char *basename)
{
    /* find the last occurrence of '.' in basename */
    const char *result = (basename ? strrchr(basename, '.') : NULL);

    /* if no '.' was found then return pointer to end of basename */
    if (basename && !result)
        result = basename + strlen(basename);

    /* special case: basenames with a single leading dot (eg ".foo") are not considered as true extensions */
    if (basename && result == basename)
        result = basename + strlen(basename);

    /* special case: empty extensions (eg "foo.","foo..") are not considered as true extensions */
    if (basename && result && result[1] == '\0')
        result = basename + strlen(basename);

    return result;
}