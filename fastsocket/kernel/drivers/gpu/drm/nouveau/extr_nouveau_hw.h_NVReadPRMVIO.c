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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ card_type; } ;

/* Variables and functions */
 scalar_t__ NV_40 ; 
 scalar_t__ NV_PRMVIO_SIZE ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_rd08 (struct nouveau_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t NVReadPRMVIO(struct drm_device *dev,
					int head, uint32_t reg)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	uint8_t val;

	/* Only NV4x have two pvio ranges; other twoHeads cards MUST call
	 * NVSetOwner for the relevant head to be programmed */
	if (head && nv_device(drm->device)->card_type == NV_40)
		reg += NV_PRMVIO_SIZE;

	val = nv_rd08(device, reg);
	return val;
}