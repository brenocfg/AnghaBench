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
struct nv17_tv_state {int ptv_208; int /*<<< orphan*/  vfilter; int /*<<< orphan*/  hfilter2; int /*<<< orphan*/  hfilter; } ;
struct nv17_tv_encoder {int /*<<< orphan*/  overscan; struct nv17_tv_state state; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_PTV_HFILTER ; 
 int /*<<< orphan*/  NV_PTV_HFILTER2 ; 
 int /*<<< orphan*/  NV_PTV_VFILTER ; 
 int calc_overscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_load_ptv (struct drm_device*,struct nv17_tv_state*,int) ; 
 struct nv17_tv_encoder* to_tv_enc (struct drm_encoder*) ; 
 int /*<<< orphan*/  tv_load_filter (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_setup_filter (struct drm_encoder*) ; 

void nv17_tv_update_rescaler(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	struct nv17_tv_state *regs = &tv_enc->state;

	regs->ptv_208 = 0x40 | (calc_overscan(tv_enc->overscan) << 8);

	tv_setup_filter(encoder);

	nv_load_ptv(dev, regs, 208);
	tv_load_filter(dev, NV_PTV_HFILTER, regs->hfilter);
	tv_load_filter(dev, NV_PTV_HFILTER2, regs->hfilter2);
	tv_load_filter(dev, NV_PTV_VFILTER, regs->vfilter);
}