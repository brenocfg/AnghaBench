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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_os_dir_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dirstruct; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ apr_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ apr_pcalloc (int /*<<< orphan*/ *,int) ; 

apr_status_t apr_os_dir_put(apr_dir_t **dir, apr_os_dir_t *thedir,
                          apr_pool_t *pool)
{
    if ((*dir) == NULL) {
        (*dir) = (apr_dir_t *)apr_pcalloc(pool, sizeof(apr_dir_t));
        (*dir)->pool = pool;
    }
    (*dir)->dirstruct = thedir;
    return APR_SUCCESS;
}