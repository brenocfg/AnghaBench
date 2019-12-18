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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_dbd_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p ; 

__attribute__((used)) static void test_dbd_init(abts_case *tc, void *data)
{
    apr_pool_t *pool = p;
    apr_status_t rv;

    rv = apr_dbd_init(pool);
    ABTS_ASSERT(tc, "failed to init apr_dbd", rv == APR_SUCCESS);
}