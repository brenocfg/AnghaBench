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
 int /*<<< orphan*/  FILESEPARATOR1 ; 
 int /*<<< orphan*/  FILESEPARATOR2 ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * arg_basename(const char *filename)
{
    const char *result = NULL, *result1, *result2;

    /* Find the last occurrence of eother file separator character. */
    /* Two alternative file separator chars are supported as legal  */
    /* file separators but not both together in the same filename.  */
    result1 = (filename ? strrchr(filename, FILESEPARATOR1) : NULL);
    result2 = (filename ? strrchr(filename, FILESEPARATOR2) : NULL);

    if (result2)
        result = result2 + 1;  /* using FILESEPARATOR2 (the alternative file separator) */

    if (result1)
        result = result1 + 1;  /* using FILESEPARATOR1 (the preferred file separator) */

    if (!result)
        result = filename;  /* neither file separator was found so basename is the whole filename */

    /* special cases of "." and ".." are not considered basenames */
    if (result && ( strcmp(".", result) == 0 || strcmp("..", result) == 0 ))
        result = filename + strlen(filename);

    return result;
}