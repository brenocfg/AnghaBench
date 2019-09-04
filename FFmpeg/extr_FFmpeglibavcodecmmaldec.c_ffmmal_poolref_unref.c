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
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ FFPoolRef ;

/* Variables and functions */
 int atomic_fetch_add_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_order_acq_rel ; 
 int /*<<< orphan*/  mmal_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmmal_poolref_unref(FFPoolRef *ref)
{
    if (ref &&
        atomic_fetch_add_explicit(&ref->refcount, -1, memory_order_acq_rel) == 1) {
        mmal_pool_destroy(ref->pool);
        av_free(ref);
    }
}