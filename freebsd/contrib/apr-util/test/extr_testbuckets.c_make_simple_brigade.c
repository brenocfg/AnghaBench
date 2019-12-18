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
typedef  int /*<<< orphan*/  apr_bucket_brigade ;
typedef  int /*<<< orphan*/  apr_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_bucket ;

/* Variables and functions */
 int /*<<< orphan*/  APR_BRIGADE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_brigade_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_transient_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static apr_bucket_brigade *make_simple_brigade(apr_bucket_alloc_t *ba,
                                               const char *first, 
                                               const char *second)
{
    apr_bucket_brigade *bb = apr_brigade_create(p, ba);
    apr_bucket *e;
 
    e = apr_bucket_transient_create(first, strlen(first), ba);
    APR_BRIGADE_INSERT_TAIL(bb, e);

    e = apr_bucket_transient_create(second, strlen(second), ba);
    APR_BRIGADE_INSERT_TAIL(bb, e);

    return bb;
}