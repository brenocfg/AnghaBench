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
 int /*<<< orphan*/  APR_BRIGADE_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  APR_BRIGADE_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  APR_BRIGADE_LAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_brigade_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_brigade_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_brigade_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_bucket_alloc_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bucket_alloc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_bucket_heap_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_bucket_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* hello ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  test_bucket_content (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void test_write_split(abts_case *tc, void *data)
{
    apr_bucket_alloc_t *ba = apr_bucket_alloc_create(p);
    apr_bucket_brigade *bb1 = apr_brigade_create(p, ba);
    apr_bucket_brigade *bb2;
    apr_bucket *e;

    e = apr_bucket_heap_create(hello, strlen(hello), NULL, ba);
    APR_BRIGADE_INSERT_HEAD(bb1, e);
    apr_bucket_split(e, strlen("hello, "));
    bb2 = apr_brigade_split(bb1, APR_BRIGADE_LAST(bb1));
    apr_brigade_write(bb1, NULL, NULL, "foo", strlen("foo"));
    test_bucket_content(tc, APR_BRIGADE_FIRST(bb2), "world", 5);

    apr_brigade_destroy(bb1);
    apr_brigade_destroy(bb2);
    apr_bucket_alloc_destroy(ba);
}