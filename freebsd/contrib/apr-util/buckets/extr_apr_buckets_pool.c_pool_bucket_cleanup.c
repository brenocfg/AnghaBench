#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/ * base; TYPE_1__ heap; int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ apr_bucket_pool ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_bucket_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t pool_bucket_cleanup(void *data)
{
    apr_bucket_pool *p = data;

    /*
     * If the pool gets cleaned up, we have to copy the data out
     * of the pool and onto the heap.  But the apr_buckets out there
     * that point to this pool bucket need to be notified such that
     * they can morph themselves into a regular heap bucket the next
     * time they try to read.  To avoid having to manipulate
     * reference counts and b->data pointers, the apr_bucket_pool
     * actually _contains_ an apr_bucket_heap as its first element,
     * so the two share their apr_bucket_refcount member, and you
     * can typecast a pool bucket struct to make it look like a
     * regular old heap bucket struct.
     */
    p->heap.base = apr_bucket_alloc(p->heap.alloc_len, p->list);
    memcpy(p->heap.base, p->base, p->heap.alloc_len);
    p->base = NULL;
    p->pool = NULL;

    return APR_SUCCESS;
}