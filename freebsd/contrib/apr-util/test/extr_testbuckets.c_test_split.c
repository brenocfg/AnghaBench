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
 int /*<<< orphan*/ * APR_BRIGADE_LAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_brigade_split (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_alloc_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bucket_alloc_destroy (int /*<<< orphan*/ *) ; 
 int count_buckets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flatten_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * make_simple_brigade (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static void test_split(abts_case *tc, void *data)
{
    apr_bucket_alloc_t *ba = apr_bucket_alloc_create(p);
    apr_bucket_brigade *bb, *bb2;
    apr_bucket *e;

    bb = make_simple_brigade(ba, "hello, ", "world");

    /* split at the "world" bucket */
    e = APR_BRIGADE_LAST(bb);
    bb2 = apr_brigade_split(bb, e);

    ABTS_ASSERT(tc, "split brigade contains one bucket",
                count_buckets(bb2) == 1);
    ABTS_ASSERT(tc, "original brigade contains one bucket",
                count_buckets(bb) == 1);

    flatten_match(tc, "match original brigade", bb, "hello, ");
    flatten_match(tc, "match split brigade", bb2, "world");

    apr_brigade_destroy(bb2);
    apr_brigade_destroy(bb);
    apr_bucket_alloc_destroy(ba);
}