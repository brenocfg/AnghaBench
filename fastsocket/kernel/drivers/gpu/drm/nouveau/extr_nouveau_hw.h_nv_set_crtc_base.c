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
typedef  int uint32_t ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ card_type; } ;

/* Variables and functions */
 int NVReadVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteCRTC (struct drm_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NV_04 ; 
 int /*<<< orphan*/  NV_CIO_CRE_HEB__INDEX ; 
 int /*<<< orphan*/  NV_PCRTC_START ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
nv_set_crtc_base(struct drm_device *dev, int head, uint32_t offset)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	NVWriteCRTC(dev, head, NV_PCRTC_START, offset);

	if (nv_device(drm->device)->card_type == NV_04) {
		/*
		 * Hilarious, the 24th bit doesn't want to stick to
		 * PCRTC_START...
		 */
		int cre_heb = NVReadVgaCrtc(dev, head, NV_CIO_CRE_HEB__INDEX);

		NVWriteVgaCrtc(dev, head, NV_CIO_CRE_HEB__INDEX,
			       (cre_heb & ~0x40) | ((offset >> 18) & 0x40));
	}
}