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
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ apr_initialize () ; 
 int /*<<< orphan*/  apr_pool_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_tag (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  apr_terminate ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 

void initialize(void) {
    if (apr_initialize() != APR_SUCCESS) {
        abort();
    }
    atexit(apr_terminate);
    
    apr_pool_create(&p, NULL);
    apr_pool_tag(p, "apr-util global test pool");
}