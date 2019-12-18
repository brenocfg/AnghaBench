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
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_disp {TYPE_1__* vblank; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int index_nr; } ;

/* Variables and functions */
 int EIO ; 
 struct nouveau_disp* nouveau_disp (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_event_enable_locked (TYPE_1__*,int) ; 

__attribute__((used)) static int
nouveau_drm_vblank_enable(struct drm_device *dev, int head)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_disp *pdisp = nouveau_disp(drm->device);

	if (head >= pdisp->vblank->index_nr)
		return -EIO;
	nouveau_event_enable_locked(pdisp->vblank, head);
	return 0;
}