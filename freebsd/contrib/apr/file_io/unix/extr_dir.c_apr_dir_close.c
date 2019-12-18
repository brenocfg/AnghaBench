#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ apr_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pool_cleanup_run (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_cleanup ; 

apr_status_t apr_dir_close(apr_dir_t *thedir)
{
    return apr_pool_cleanup_run(thedir->pool, thedir, dir_cleanup);
}