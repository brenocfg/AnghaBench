#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  se_zbias_constant; int /*<<< orphan*/  se_zbias_factor; } ;
struct TYPE_5__ {int dirty; int /*<<< orphan*/  tex; int /*<<< orphan*/  context; TYPE_1__ context2; } ;
typedef  TYPE_2__ drm_radeon_state_t ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CP_PACKET0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_SE_ZBIAS_FACTOR ; 
 int RADEON_UPLOAD_ZBIAS ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int radeon_emit_state (int /*<<< orphan*/ *,struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int radeon_emit_state2(drm_radeon_private_t * dev_priv,
			      struct drm_file *file_priv,
			      drm_radeon_state_t * state)
{
	RING_LOCALS;

	if (state->dirty & RADEON_UPLOAD_ZBIAS) {
		BEGIN_RING(3);
		OUT_RING(CP_PACKET0(RADEON_SE_ZBIAS_FACTOR, 1));
		OUT_RING(state->context2.se_zbias_factor);
		OUT_RING(state->context2.se_zbias_constant);
		ADVANCE_RING();
	}

	return radeon_emit_state(dev_priv, file_priv, &state->context,
				 state->tex, state->dirty);
}