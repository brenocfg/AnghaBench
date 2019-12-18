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
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_LP_RING () ; 
 int BEGIN_LP_RING (int) ; 
 int EINVAL ; 
 TYPE_1__* LP_RING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int validate_cmd (int) ; 

__attribute__((used)) static int i915_emit_cmds(struct drm_device * dev, int *buffer, int dwords)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int i, ret;

	if ((dwords+1) * sizeof(int) >= LP_RING(dev_priv)->size - 8)
		return -EINVAL;

	for (i = 0; i < dwords;) {
		int sz = validate_cmd(buffer[i]);
		if (sz == 0 || i + sz > dwords)
			return -EINVAL;
		i += sz;
	}

	ret = BEGIN_LP_RING((dwords+1)&~1);
	if (ret)
		return ret;

	for (i = 0; i < dwords; i++)
		OUT_RING(buffer[i]);
	if (dwords & 1)
		OUT_RING(0);

	ADVANCE_LP_RING();

	return 0;
}