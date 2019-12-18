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
struct TYPE_4__ {int /*<<< orphan*/  shared_state; } ;
typedef  TYPE_1__ VG_CLIENT_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_platform_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vg_client_shared_state_release (int /*<<< orphan*/ ) ; 

void vg_client_state_free(VG_CLIENT_STATE_T *state)
{
   vg_client_shared_state_release(state->shared_state);
   khrn_platform_free(state);
}