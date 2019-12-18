#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  base; int /*<<< orphan*/  (* free_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ apr_bucket_heap ;

/* Variables and functions */
 int /*<<< orphan*/  apr_bucket_free (TYPE_1__*) ; 
 scalar_t__ apr_bucket_shared_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void heap_bucket_destroy(void *data)
{
    apr_bucket_heap *h = data;

    if (apr_bucket_shared_destroy(h)) {
        (*h->free_func)(h->base);
        apr_bucket_free(h);
    }
}