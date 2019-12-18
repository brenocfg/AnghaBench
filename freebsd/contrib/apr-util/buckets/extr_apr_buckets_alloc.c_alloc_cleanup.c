#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_2__ {scalar_t__ allocator; scalar_t__ pool; int /*<<< orphan*/  blocks; } ;
typedef  TYPE_1__ apr_bucket_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_allocator_destroy (scalar_t__) ; 
 int /*<<< orphan*/  apr_allocator_free (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_pool_allocator_get (scalar_t__) ; 

__attribute__((used)) static apr_status_t alloc_cleanup(void *data)
{
    apr_bucket_alloc_t *list = data;

    apr_allocator_free(list->allocator, list->blocks);

#if APR_POOL_DEBUG
    if (list->pool && list->allocator != apr_pool_allocator_get(list->pool)) {
        apr_allocator_destroy(list->allocator);
    }
#endif

    return APR_SUCCESS;
}