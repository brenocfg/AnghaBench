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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const PATH_SEPARATOR ; 
 char const* apr_pstrndup (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *path_canonicalize (const char *path, apr_pool_t *pool)
{
    /* At some point this could eliminate redundant components.  For
     * now, it just makes sure there is no trailing slash. */
    apr_size_t len = strlen (path);
    apr_size_t orig_len = len;
    
    while ((len > 0) && (path[len - 1] == PATH_SEPARATOR))
        len--;
    
    if (len != orig_len)
        return apr_pstrndup (pool, path, len);
    else
        return path;
}