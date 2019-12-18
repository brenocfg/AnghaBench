#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct nvbios_init {int offset; int execute; int /*<<< orphan*/  crtc; int /*<<< orphan*/  outp; struct nouveau_bios* bios; int /*<<< orphan*/  subdev; } ;
struct nouveau_disp {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct TYPE_3__ {scalar_t__ lnkcmp; } ;
struct dp_state {int link_nr; int link_bw; int* dpcd; int version; int /*<<< orphan*/  head; int /*<<< orphan*/  outp; struct nouveau_disp* disp; TYPE_2__* func; TYPE_1__ info; int /*<<< orphan*/  aux; } ;
struct TYPE_4__ {int (* lnk_ctl ) (struct nouveau_disp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int /*<<< orphan*/  DPCD_LC00 ; 
 int DPCD_LC01_ENHANCED_FRAME_EN ; 
 size_t DPCD_RC02 ; 
 int DPCD_RC02_ENHANCED_FRAME_CAP ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_disp*) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nv_subdev (struct nouveau_disp*) ; 
 int /*<<< orphan*/  nv_wraux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  nvbios_exec (struct nvbios_init*) ; 
 int stub1 (struct nouveau_disp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
dp_set_link_config(struct dp_state *dp)
{
	struct nouveau_disp *disp = dp->disp;
	struct nouveau_bios *bios = nouveau_bios(disp);
	struct nvbios_init init = {
		.subdev = nv_subdev(dp->disp),
		.bios = bios,
		.offset = 0x0000,
		.outp = dp->outp,
		.crtc = dp->head,
		.execute = 1,
	};
	u32 lnkcmp;
	u8 sink[2];

	DBG("%d lanes at %d KB/s\n", dp->link_nr, dp->link_bw);

	/* set desired link configuration on the sink */
	sink[0] = dp->link_bw / 27000;
	sink[1] = dp->link_nr;
	if (dp->dpcd[DPCD_RC02] & DPCD_RC02_ENHANCED_FRAME_CAP)
		sink[1] |= DPCD_LC01_ENHANCED_FRAME_EN;

	nv_wraux(dp->aux, DPCD_LC00, sink, 2);

	/* set desired link configuration on the source */
	if ((lnkcmp = dp->info.lnkcmp)) {
		if (dp->version < 0x30) {
			while ((dp->link_bw / 10) < nv_ro16(bios, lnkcmp))
				lnkcmp += 4;
			init.offset = nv_ro16(bios, lnkcmp + 2);
		} else {
			while ((dp->link_bw / 27000) < nv_ro08(bios, lnkcmp))
				lnkcmp += 3;
			init.offset = nv_ro16(bios, lnkcmp + 1);
		}

		nvbios_exec(&init);
	}

	return dp->func->lnk_ctl(dp->disp, dp->outp, dp->head,
				 dp->link_nr, dp->link_bw / 27000,
				 dp->dpcd[DPCD_RC02] &
					  DPCD_RC02_ENHANCED_FRAME_CAP);
}