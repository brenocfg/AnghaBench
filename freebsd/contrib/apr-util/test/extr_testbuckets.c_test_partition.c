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
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  APR_BRIGADE_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  APR_BRIGADE_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  APR_BRIGADE_LAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * APR_BRIGADE_SENTINEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_assert_success (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * apr_brigade_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_destroy (int /*<<< orphan*/ *) ; 
 int apr_brigade_partition (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * apr_bucket_alloc_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bucket_alloc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_immortal_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hello ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bucket_content (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void test_partition(abts_case *tc, void *data)
{
    apr_bucket_alloc_t *ba = apr_bucket_alloc_create(p);
    apr_bucket_brigade *bb = apr_brigade_create(p, ba);
    apr_bucket *e;

    e = apr_bucket_immortal_create(hello, strlen(hello), ba);
    APR_BRIGADE_INSERT_HEAD(bb, e);

    apr_assert_success(tc, "partition brigade",
                       apr_brigade_partition(bb, 5, &e));

    test_bucket_content(tc, APR_BRIGADE_FIRST(bb),
                        "hello", 5);

    test_bucket_content(tc, APR_BRIGADE_LAST(bb),
                        ", world", 7);

    ABTS_ASSERT(tc, "partition returns APR_INCOMPLETE",
                apr_brigade_partition(bb, 8192, &e));

    ABTS_ASSERT(tc, "APR_INCOMPLETE partition returned sentinel",
                e == APR_BRIGADE_SENTINEL(bb));

    apr_brigade_destroy(bb);
    apr_bucket_alloc_destroy(ba);
}