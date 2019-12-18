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
typedef  int /*<<< orphan*/  apr_os_dir_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dirstruct; } ;
typedef  TYPE_1__ apr_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_ENODIR ; 
 int /*<<< orphan*/  APR_SUCCESS ; 

apr_status_t apr_os_dir_get(apr_os_dir_t **thedir, apr_dir_t *dir)
{
    if (dir == NULL) {
        return APR_ENODIR;
    }
    *thedir = dir->dirstruct;
    return APR_SUCCESS;
}