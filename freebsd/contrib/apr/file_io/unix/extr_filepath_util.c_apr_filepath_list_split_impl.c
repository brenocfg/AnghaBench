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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ apr_array_push (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* apr_strtok (char*,char*,char**) ; 
 char* strchr (char*,char) ; 

apr_status_t apr_filepath_list_split_impl(apr_array_header_t **pathelts,
                                          const char *liststr,
                                          char separator,
                                          apr_pool_t *p)
{
    char *path, *part, *ptr;
    char separator_string[2] = { '\0', '\0' };
    apr_array_header_t *elts;
    int nelts;

    separator_string[0] = separator;
    /* Count the number of path elements. We know there'll be at least
       one even if path is an empty string. */
    path = apr_pstrdup(p, liststr);
    for (nelts = 0, ptr = path; ptr != NULL; ++nelts)
    {
        ptr = strchr(ptr, separator);
        if (ptr)
            ++ptr;
    }

    /* Split the path into the array. */
    elts = apr_array_make(p, nelts, sizeof(char*));
    while ((part = apr_strtok(path, separator_string, &ptr)) != NULL)
    {
        if (*part == '\0')      /* Ignore empty path components. */
            continue;

        *(char**)apr_array_push(elts) = part;
        path = NULL;            /* For the next call to apr_strtok */
    }

    *pathelts = elts;
    return APR_SUCCESS;
}