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
typedef  int /*<<< orphan*/  buf ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_bucket_brigade ;
typedef  int /*<<< orphan*/  apr_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_bucket ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_STR_NEQUAL (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_BRIGADE_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_assert_success (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_brigade_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_flatten (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  apr_brigade_putstrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/ * apr_bucket_alloc_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bucket_alloc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_heap_create (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void test_write_putstrs(abts_case *tc, void *data)
{
    apr_bucket_alloc_t *ba = apr_bucket_alloc_create(p);
    apr_bucket_brigade *bb = apr_brigade_create(p, ba);
    apr_bucket *e;
    char buf[30];
    apr_size_t len = sizeof(buf);
    const char *expect = "123456789abcdefghij";

    e = apr_bucket_heap_create("1", 1, NULL, ba);
    APR_BRIGADE_INSERT_HEAD(bb, e);

    apr_brigade_putstrs(bb, NULL, NULL, "2", "34", "567", "8", "9a", "bcd",
                        "e", "f", "gh", "i", NULL);
    apr_brigade_putstrs(bb, NULL, NULL, "j", NULL);
    apr_assert_success(tc, "apr_brigade_flatten",
                       apr_brigade_flatten(bb, buf, &len));
    ABTS_STR_NEQUAL(tc, expect, buf, strlen(expect));

    apr_brigade_destroy(bb);
    apr_bucket_alloc_destroy(ba);
}