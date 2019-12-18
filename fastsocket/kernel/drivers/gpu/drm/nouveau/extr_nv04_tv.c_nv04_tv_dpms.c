#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct nv04_mode_state {int pllsel; } ;
struct nouveau_encoder {TYPE_1__* dcb; } ;
struct nouveau_drm {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* dpms ) (struct drm_encoder*,int) ;} ;
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {struct nv04_mode_state mode_reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int NVReadVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_CIO_CRE_RPC1_INDEX ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_PRAMDAC_PLL_COEFF_SELECT ; 
 int PLLSEL_TV_CRTC1_MASK ; 
 int PLLSEL_TV_CRTC2_MASK ; 
 TYPE_4__* get_slave_funcs (struct drm_encoder*) ; 
 TYPE_3__* nouveau_crtc (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 TYPE_2__* nv04_display (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,int) ; 

__attribute__((used)) static void nv04_tv_dpms(struct drm_encoder *encoder, int mode)
{
	struct drm_device *dev = encoder->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	uint8_t crtc1A;

	NV_DEBUG(drm, "Setting dpms mode %d on TV encoder (output %d)\n",
		 mode, nv_encoder->dcb->index);

	state->pllsel &= ~(PLLSEL_TV_CRTC1_MASK | PLLSEL_TV_CRTC2_MASK);

	if (mode == DRM_MODE_DPMS_ON) {
		int head = nouveau_crtc(encoder->crtc)->index;
		crtc1A = NVReadVgaCrtc(dev, head, NV_CIO_CRE_RPC1_INDEX);

		state->pllsel |= head ? PLLSEL_TV_CRTC2_MASK :
					PLLSEL_TV_CRTC1_MASK;

		/* Inhibit hsync */
		crtc1A |= 0x80;

		NVWriteVgaCrtc(dev, head, NV_CIO_CRE_RPC1_INDEX, crtc1A);
	}

	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_PLL_COEFF_SELECT, state->pllsel);

	get_slave_funcs(encoder)->dpms(encoder, mode);
}