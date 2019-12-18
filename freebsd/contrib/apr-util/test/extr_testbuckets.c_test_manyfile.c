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
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_bucket_brigade ;
typedef  int /*<<< orphan*/  apr_bucket_alloc_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_brigade_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_insert_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_bucket_alloc_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bucket_alloc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flatten_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * make_test_file (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static void test_manyfile(abts_case *tc, void *data)
{
    apr_bucket_alloc_t *ba = apr_bucket_alloc_create(p);
    apr_bucket_brigade *bb = apr_brigade_create(p, ba);
    apr_file_t *f;

    f = make_test_file(tc, "manyfile.bin",
                       "world" "hello" "brave" " ,\n");

    apr_brigade_insert_file(bb, f, 5, 5, p);
    apr_brigade_insert_file(bb, f, 16, 1, p);
    apr_brigade_insert_file(bb, f, 15, 1, p);
    apr_brigade_insert_file(bb, f, 10, 5, p);
    apr_brigade_insert_file(bb, f, 15, 1, p);
    apr_brigade_insert_file(bb, f, 0, 5, p);
    apr_brigade_insert_file(bb, f, 17, 1, p);

    /* can you tell what it is yet? */
    flatten_match(tc, "file seek test", bb,
                  "hello, brave world\n");

    apr_file_close(f);
    apr_brigade_destroy(bb);
    apr_bucket_alloc_destroy(ba);
}