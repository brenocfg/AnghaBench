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
struct TYPE_2__ {scalar_t__ pll; scalar_t__ clk; } ;
struct nva3_pm_state {TYPE_1__ mclk; int /*<<< orphan*/  vdec; int /*<<< orphan*/  unka0; int /*<<< orphan*/  sclk; int /*<<< orphan*/  nclk; } ;
struct nouveau_drm {int dummy; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  kfree (struct nva3_pm_state*) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_device*,int,int,int) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nouveau_device*,int,int,int) ; 
 int /*<<< orphan*/  nv_wait_cb (struct nouveau_device*,int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 
 int /*<<< orphan*/  nva3_pm_grcp_idle ; 
 int /*<<< orphan*/  prog_clk (struct drm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prog_mem (struct drm_device*,struct nva3_pm_state*) ; 
 int /*<<< orphan*/  prog_pll (struct drm_device*,int,int,int /*<<< orphan*/ *) ; 

int
nva3_pm_clocks_set(struct drm_device *dev, void *pre_state)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nva3_pm_state *info = pre_state;
	int ret = -EAGAIN;

	/* prevent any new grctx switches from starting */
	nv_wr32(device, 0x400324, 0x00000000);
	nv_wr32(device, 0x400328, 0x0050001c); /* wait flag 0x1c */
	/* wait for any pending grctx switches to complete */
	if (!nv_wait_cb(device, nva3_pm_grcp_idle, dev)) {
		NV_ERROR(drm, "pm: ctxprog didn't go idle\n");
		goto cleanup;
	}
	/* freeze PFIFO */
	nv_mask(device, 0x002504, 0x00000001, 0x00000001);
	if (!nv_wait(device, 0x002504, 0x00000010, 0x00000010)) {
		NV_ERROR(drm, "pm: fifo didn't go idle\n");
		goto cleanup;
	}

	prog_pll(dev, 0x00, 0x004200, &info->nclk);
	prog_pll(dev, 0x01, 0x004220, &info->sclk);
	prog_clk(dev, 0x20, &info->unka0);
	prog_clk(dev, 0x21, &info->vdec);

	if (info->mclk.clk || info->mclk.pll)
		prog_mem(dev, info);

	ret = 0;

cleanup:
	/* unfreeze PFIFO */
	nv_mask(device, 0x002504, 0x00000001, 0x00000000);
	/* restore ctxprog to normal */
	nv_wr32(device, 0x400324, 0x00000000);
	nv_wr32(device, 0x400328, 0x0070009c); /* set flag 0x1c */
	/* unblock it if necessary */
	if (nv_rd32(device, 0x400308) == 0x0050001c)
		nv_mask(device, 0x400824, 0x10000000, 0x10000000);
	kfree(info);
	return ret;
}