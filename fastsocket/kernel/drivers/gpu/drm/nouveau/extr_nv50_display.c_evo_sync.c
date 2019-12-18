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
typedef  int /*<<< orphan*/  u32 ;
struct nv50_mast {int dummy; } ;
struct nv50_disp {int /*<<< orphan*/  sync; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EVO_MAST_NTFY ; 
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,struct nv50_mast*) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  evo_sync_wait ; 
 int /*<<< orphan*/ * evo_wait (struct nv50_mast*,int) ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (int /*<<< orphan*/ ,int,int) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nv50_disp* nv50_disp (struct drm_device*) ; 
 struct nv50_mast* nv50_mast (struct drm_device*) ; 
 scalar_t__ nv_wait_cb (struct nouveau_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evo_sync(struct drm_device *dev)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nv50_disp *disp = nv50_disp(dev);
	struct nv50_mast *mast = nv50_mast(dev);
	u32 *push = evo_wait(mast, 8);
	if (push) {
		nouveau_bo_wr32(disp->sync, EVO_MAST_NTFY, 0x00000000);
		evo_mthd(push, 0x0084, 1);
		evo_data(push, 0x80000000 | EVO_MAST_NTFY);
		evo_mthd(push, 0x0080, 2);
		evo_data(push, 0x00000000);
		evo_data(push, 0x00000000);
		evo_kick(push, mast);
		if (nv_wait_cb(device, evo_sync_wait, disp->sync))
			return 0;
	}

	return -EBUSY;
}