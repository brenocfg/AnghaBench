#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_3__ {int r_t; int c_m; } ;
struct TYPE_4__ {int mem_freq; int fsb_freq; TYPE_1__ ips; } ;
typedef  TYPE_2__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIPLL0 ; 
 int /*<<< orphan*/  DDRMPLL1 ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int I915_READ16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_ironlake_get_mem_freq(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u16 ddrpll, csipll;

	ddrpll = I915_READ16(DDRMPLL1);
	csipll = I915_READ16(CSIPLL0);

	switch (ddrpll & 0xff) {
	case 0xc:
		dev_priv->mem_freq = 800;
		break;
	case 0x10:
		dev_priv->mem_freq = 1066;
		break;
	case 0x14:
		dev_priv->mem_freq = 1333;
		break;
	case 0x18:
		dev_priv->mem_freq = 1600;
		break;
	default:
		DRM_DEBUG_DRIVER("unknown memory frequency 0x%02x\n",
				 ddrpll & 0xff);
		dev_priv->mem_freq = 0;
		break;
	}

	dev_priv->ips.r_t = dev_priv->mem_freq;

	switch (csipll & 0x3ff) {
	case 0x00c:
		dev_priv->fsb_freq = 3200;
		break;
	case 0x00e:
		dev_priv->fsb_freq = 3733;
		break;
	case 0x010:
		dev_priv->fsb_freq = 4266;
		break;
	case 0x012:
		dev_priv->fsb_freq = 4800;
		break;
	case 0x014:
		dev_priv->fsb_freq = 5333;
		break;
	case 0x016:
		dev_priv->fsb_freq = 5866;
		break;
	case 0x018:
		dev_priv->fsb_freq = 6400;
		break;
	default:
		DRM_DEBUG_DRIVER("unknown fsb frequency 0x%04x\n",
				 csipll & 0x3ff);
		dev_priv->fsb_freq = 0;
		break;
	}

	if (dev_priv->fsb_freq == 3200) {
		dev_priv->ips.c_m = 0;
	} else if (dev_priv->fsb_freq > 3200 && dev_priv->fsb_freq <= 4800) {
		dev_priv->ips.c_m = 1;
	} else {
		dev_priv->ips.c_m = 2;
	}
}