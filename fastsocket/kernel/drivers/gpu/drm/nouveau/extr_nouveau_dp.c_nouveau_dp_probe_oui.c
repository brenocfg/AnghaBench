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
typedef  int u8 ;
struct nouveau_i2c_port {int dummy; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_BRANCH_OUI ; 
 size_t DP_DOWN_STREAM_PORT_COUNT ; 
 int DP_OUI_SUPPORT ; 
 int /*<<< orphan*/  DP_SINK_OUI ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nv_rdaux (struct nouveau_i2c_port*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
nouveau_dp_probe_oui(struct drm_device *dev, struct nouveau_i2c_port *auxch,
		     u8 *dpcd)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	u8 buf[3];

	if (!(dpcd[DP_DOWN_STREAM_PORT_COUNT] & DP_OUI_SUPPORT))
		return;

	if (!nv_rdaux(auxch, DP_SINK_OUI, buf, 3))
		NV_DEBUG(drm, "Sink OUI: %02hx%02hx%02hx\n",
			     buf[0], buf[1], buf[2]);

	if (!nv_rdaux(auxch, DP_BRANCH_OUI, buf, 3))
		NV_DEBUG(drm, "Branch OUI: %02hx%02hx%02hx\n",
			     buf[0], buf[1], buf[2]);

}