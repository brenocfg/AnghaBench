#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nouveau_i2c_port {int dummy; } ;
struct TYPE_6__ {int* dpcd; int link_bw; int link_nr; } ;
struct nouveau_encoder {TYPE_3__ dp; TYPE_2__* dcb; struct nouveau_i2c_port* i2c; } ;
struct nouveau_drm {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int link_nr; int link_bw; } ;
struct TYPE_5__ {TYPE_1__ dpconf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_REV ; 
 int DP_MAX_LANE_COUNT_MASK ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int,...) ; 
 int /*<<< orphan*/  nouveau_dp_probe_oui (struct drm_device*,struct nouveau_i2c_port*,int*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 int nv_rdaux (struct nouveau_i2c_port*,int /*<<< orphan*/ ,int*,int) ; 

bool
nouveau_dp_detect(struct drm_encoder *encoder)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct drm_device *dev = encoder->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_i2c_port *auxch;
	u8 *dpcd = nv_encoder->dp.dpcd;
	int ret;

	auxch = nv_encoder->i2c;
	if (!auxch)
		return false;

	ret = nv_rdaux(auxch, DP_DPCD_REV, dpcd, 8);
	if (ret)
		return false;

	nv_encoder->dp.link_bw = 27000 * dpcd[1];
	nv_encoder->dp.link_nr = dpcd[2] & DP_MAX_LANE_COUNT_MASK;

	NV_DEBUG(drm, "display: %dx%d dpcd 0x%02x\n",
		     nv_encoder->dp.link_nr, nv_encoder->dp.link_bw, dpcd[0]);
	NV_DEBUG(drm, "encoder: %dx%d\n",
		     nv_encoder->dcb->dpconf.link_nr,
		     nv_encoder->dcb->dpconf.link_bw);

	if (nv_encoder->dcb->dpconf.link_nr < nv_encoder->dp.link_nr)
		nv_encoder->dp.link_nr = nv_encoder->dcb->dpconf.link_nr;
	if (nv_encoder->dcb->dpconf.link_bw < nv_encoder->dp.link_bw)
		nv_encoder->dp.link_bw = nv_encoder->dcb->dpconf.link_bw;

	NV_DEBUG(drm, "maximum: %dx%d\n",
		     nv_encoder->dp.link_nr, nv_encoder->dp.link_bw);

	nouveau_dp_probe_oui(dev, auxch, dpcd);

	return true;
}