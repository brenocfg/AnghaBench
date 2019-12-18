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
 int APR_BRIGADE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * APR_BRIGADE_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  APR_BRIGADE_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * APR_BRIGADE_SENTINEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  APR_BUCKET_INSERT_BEFORE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * APR_BUCKET_NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * APR_BUCKET_PREV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_brigade_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_alloc_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bucket_alloc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_flush_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_transient_create (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static void test_simple(abts_case *tc, void *data)
{
    apr_bucket_alloc_t *ba;
    apr_bucket_brigade *bb;
    apr_bucket *fb, *tb;
    
    ba = apr_bucket_alloc_create(p);
    bb = apr_brigade_create(p, ba);
    
    fb = APR_BRIGADE_FIRST(bb);
    ABTS_ASSERT(tc, "first bucket of empty brigade is sentinel",
                fb == APR_BRIGADE_SENTINEL(bb));

    fb = apr_bucket_flush_create(ba);
    APR_BRIGADE_INSERT_HEAD(bb, fb);

    ABTS_ASSERT(tc, "first bucket of brigade is flush",
                APR_BRIGADE_FIRST(bb) == fb);

    ABTS_ASSERT(tc, "bucket after flush is sentinel",
                APR_BUCKET_NEXT(fb) == APR_BRIGADE_SENTINEL(bb));

    tb = apr_bucket_transient_create("aaa", 3, ba);
    APR_BUCKET_INSERT_BEFORE(fb, tb);

    ABTS_ASSERT(tc, "bucket before flush now transient",
                APR_BUCKET_PREV(fb) == tb);
    ABTS_ASSERT(tc, "bucket after transient is flush",
                APR_BUCKET_NEXT(tb) == fb);
    ABTS_ASSERT(tc, "bucket before transient is sentinel",
                APR_BUCKET_PREV(tb) == APR_BRIGADE_SENTINEL(bb));

    apr_brigade_cleanup(bb);

    ABTS_ASSERT(tc, "cleaned up brigade was empty", APR_BRIGADE_EMPTY(bb));

    apr_brigade_destroy(bb);
    apr_bucket_alloc_destroy(ba);
}