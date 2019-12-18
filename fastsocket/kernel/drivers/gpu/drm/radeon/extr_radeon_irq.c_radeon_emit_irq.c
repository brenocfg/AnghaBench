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
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  swi_emitted; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  OUT_RING_REG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RADEON_GEN_INT_STATUS ; 
 int /*<<< orphan*/  RADEON_LAST_SWI_REG ; 
 unsigned int RADEON_SW_INT_FIRE ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int radeon_emit_irq(struct drm_device * dev)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	unsigned int ret;
	RING_LOCALS;

	atomic_inc(&dev_priv->swi_emitted);
	ret = atomic_read(&dev_priv->swi_emitted);

	BEGIN_RING(4);
	OUT_RING_REG(RADEON_LAST_SWI_REG, ret);
	OUT_RING_REG(RADEON_GEN_INT_STATUS, RADEON_SW_INT_FIRE);
	ADVANCE_RING();
	COMMIT_RING();

	return ret;
}