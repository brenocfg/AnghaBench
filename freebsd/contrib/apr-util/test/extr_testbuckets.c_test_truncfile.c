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
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_bucket_brigade ;
typedef  int /*<<< orphan*/  apr_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_bucket ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  APR_BLOCK_READ ; 
 int /*<<< orphan*/ * APR_BRIGADE_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ APR_BRIGADE_SENTINEL (int /*<<< orphan*/ *) ; 
 scalar_t__ APR_BUCKET_NEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ APR_EOF ; 
 int /*<<< orphan*/ * apr_brigade_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_insert_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_bucket_alloc_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bucket_alloc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_bucket_file_enable_mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_bucket_read (int /*<<< orphan*/ *,char const**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_file_trunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_test_file (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static void test_truncfile(abts_case *tc, void *data)
{
    apr_bucket_alloc_t *ba = apr_bucket_alloc_create(p);
    apr_bucket_brigade *bb = apr_brigade_create(p, ba);
    apr_file_t *f = make_test_file(tc, "testfile.txt", "hello");
    apr_bucket *e;
    const char *buf;
    apr_size_t len;

    apr_brigade_insert_file(bb, f, 0, 5, p);

    apr_file_trunc(f, 0);

    e = APR_BRIGADE_FIRST(bb);

    ABTS_ASSERT(tc, "single bucket in brigade",
                APR_BUCKET_NEXT(e) == APR_BRIGADE_SENTINEL(bb));

    apr_bucket_file_enable_mmap(e, 0);

    ABTS_ASSERT(tc, "read gave APR_EOF",
                apr_bucket_read(e, &buf, &len, APR_BLOCK_READ) == APR_EOF);

    ABTS_ASSERT(tc, "read length 0", len == 0);
    
    ABTS_ASSERT(tc, "still a single bucket in brigade",
                APR_BUCKET_NEXT(e) == APR_BRIGADE_SENTINEL(bb));

    apr_file_close(f);
    apr_brigade_destroy(bb);
    apr_bucket_alloc_destroy(ba);
}