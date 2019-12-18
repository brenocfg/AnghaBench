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
struct TYPE_4__ {scalar_t__ ref_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  objects; } ;
typedef  TYPE_1__ VG_CLIENT_SHARED_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_platform_free (TYPE_1__*) ; 
 int /*<<< orphan*/  khrn_pointer_map_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khrn_pointer_map_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_free_callback ; 
 int /*<<< orphan*/  platform_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

void vg_client_shared_state_free(VG_CLIENT_SHARED_STATE_T *shared_state)
{
   vcos_assert(shared_state->ref_count == 0);
   khrn_pointer_map_iterate(&shared_state->objects, object_free_callback, NULL);
   khrn_pointer_map_term(&shared_state->objects);
   platform_mutex_destroy(&shared_state->mutex);
   khrn_platform_free(shared_state);
}