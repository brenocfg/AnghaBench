#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int elt_size; int nelts; scalar_t__ elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

apr_status_t apr_filepath_list_merge_impl(char **liststr,
                                          apr_array_header_t *pathelts,
                                          char separator,
                                          apr_pool_t *p)
{
    apr_size_t path_size = 0;
    char *path;
    int i;

    /* This test isn't 100% certain, but it'll catch at least some
       invalid uses... */
    if (pathelts->elt_size != sizeof(char*))
        return APR_EINVAL;

    /* Calculate the size of the merged path */
    for (i = 0; i < pathelts->nelts; ++i)
        path_size += strlen(((char**)pathelts->elts)[i]);

    if (path_size == 0)
    {
        *liststr = NULL;
        return APR_SUCCESS;
    }

    if (i > 0)                  /* Add space for the separators */
        path_size += (i - 1);

    /* Merge the path components */
    path = *liststr = apr_palloc(p, path_size + 1);
    for (i = 0; i < pathelts->nelts; ++i)
    {
        /* ### Hmmmm. Calling strlen twice on the same string. Yuck.
               But is is better than reallocation in apr_pstrcat? */
        const char *part = ((char**)pathelts->elts)[i];
        apr_size_t part_size = strlen(part);
        if (part_size == 0)     /* Ignore empty path components. */
            continue;

        if (i > 0)
            *path++ = separator;
        memcpy(path, part, part_size);
        path += part_size;
    }
    *path = '\0';
    return APR_SUCCESS;
}