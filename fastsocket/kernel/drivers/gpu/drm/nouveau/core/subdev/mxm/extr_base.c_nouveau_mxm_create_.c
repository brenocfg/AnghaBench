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
typedef  int /*<<< orphan*/  u16 ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_mxm {int /*<<< orphan*/  action; } ;
struct nouveau_device {int /*<<< orphan*/  cfgopt; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MXM_SANITISE_DCB ; 
 scalar_t__ mxm_shadow (struct nouveau_mxm*,int) ; 
 int /*<<< orphan*/  mxm_table (struct nouveau_bios*,int*,int*) ; 
 int /*<<< orphan*/  mxms_foreach (struct nouveau_mxm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mxms_version (struct nouveau_mxm*) ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 scalar_t__ nouveau_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int nouveau_subdev_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,char*,char*,int,void**) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_mxm*,char*) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_info (struct nouveau_mxm*,char*,...) ; 
 int nv_ro08 (struct nouveau_bios*,int /*<<< orphan*/ ) ; 

int
nouveau_mxm_create_(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, int length, void **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nouveau_bios *bios = nouveau_bios(device);
	struct nouveau_mxm *mxm;
	u8  ver, len;
	u16 data;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0, "MXM", "mxm",
				     length, pobject);
	mxm = *pobject;
	if (ret)
		return ret;

	data = mxm_table(bios, &ver, &len);
	if (!data || !(ver = nv_ro08(bios, data))) {
		nv_debug(mxm, "no VBIOS data, nothing to do\n");
		return 0;
	}

	nv_info(mxm, "BIOS version %d.%d\n", ver >> 4, ver & 0x0f);

	if (mxm_shadow(mxm, ver)) {
		nv_info(mxm, "failed to locate valid SIS\n");
#if 0
		/* we should, perhaps, fall back to some kind of limited
		 * mode here if the x86 vbios hasn't already done the
		 * work for us (so we prevent loading with completely
		 * whacked vbios tables).
		 */
		return -EINVAL;
#else
		return 0;
#endif
	}

	nv_info(mxm, "MXMS Version %d.%d\n",
		mxms_version(mxm) >> 8, mxms_version(mxm) & 0xff);
	mxms_foreach(mxm, 0, NULL, NULL);

	if (nouveau_boolopt(device->cfgopt, "NvMXMDCB", true))
		mxm->action |= MXM_SANITISE_DCB;
	return 0;
}