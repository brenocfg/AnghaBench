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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  R600_CLEAR_AGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  radeon_cs_id_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r600_cs_id_emit(drm_radeon_private_t *dev_priv, u32 *id)
{
	RING_LOCALS;

	*id = radeon_cs_id_get(dev_priv);

	/* SCRATCH 2 */
	BEGIN_RING(3);
	R600_CLEAR_AGE(*id);
	ADVANCE_RING();
	COMMIT_RING();
}