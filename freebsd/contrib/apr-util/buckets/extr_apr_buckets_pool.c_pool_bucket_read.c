#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_read_type_e ;
struct TYPE_5__ {char* base; } ;
struct TYPE_6__ {char* base; TYPE_1__ heap; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ apr_bucket_pool ;
struct TYPE_7__ {int start; int /*<<< orphan*/  length; int /*<<< orphan*/ * type; TYPE_2__* data; } ;
typedef  TYPE_3__ apr_bucket ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_bucket_type_heap ; 

__attribute__((used)) static apr_status_t pool_bucket_read(apr_bucket *b, const char **str, 
                                     apr_size_t *len, apr_read_type_e block)
{
    apr_bucket_pool *p = b->data;
    const char *base = p->base;

    if (p->pool == NULL) {
        /*
         * pool has been cleaned up... masquerade as a heap bucket from now
         * on. subsequent bucket operations will use the heap bucket code.
         */
        b->type = &apr_bucket_type_heap;
        base = p->heap.base;
    }
    *str = base + b->start;
    *len = b->length;
    return APR_SUCCESS;
}