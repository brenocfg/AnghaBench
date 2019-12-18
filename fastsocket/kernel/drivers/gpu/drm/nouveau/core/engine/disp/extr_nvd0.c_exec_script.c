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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct nvbios_outp {int /*<<< orphan*/ * script; } ;
struct nvbios_init {int crtc; int execute; struct dcb_output* outp; int /*<<< orphan*/  offset; struct nouveau_bios* bios; int /*<<< orphan*/  subdev; } ;
struct nv50_disp_priv {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct dcb_output {int dummy; } ;

/* Variables and functions */
 scalar_t__ exec_lookup (struct nv50_disp_priv*,int,int,int,struct dcb_output*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_outp*) ; 
 struct nouveau_bios* nouveau_bios (struct nv50_disp_priv*) ; 
 int nv_rd32 (struct nv50_disp_priv*,int) ; 
 int /*<<< orphan*/  nv_subdev (struct nv50_disp_priv*) ; 
 scalar_t__ nvbios_exec (struct nvbios_init*) ; 

__attribute__((used)) static bool
exec_script(struct nv50_disp_priv *priv, int head, int id)
{
	struct nouveau_bios *bios = nouveau_bios(priv);
	struct nvbios_outp info;
	struct dcb_output dcb;
	u8  ver, hdr, cnt, len;
	u32 ctrl = 0x00000000;
	u16 data;
	int outp;

	for (outp = 0; !(ctrl & (1 << head)) && outp < 8; outp++) {
		ctrl = nv_rd32(priv, 0x640180 + (outp * 0x20));
		if (ctrl & (1 << head))
			break;
	}

	if (outp == 8)
		return false;

	data = exec_lookup(priv, head, outp, ctrl, &dcb, &ver, &hdr, &cnt, &len, &info);
	if (data) {
		struct nvbios_init init = {
			.subdev = nv_subdev(priv),
			.bios = bios,
			.offset = info.script[id],
			.outp = &dcb,
			.crtc = head,
			.execute = 1,
		};

		return nvbios_exec(&init) == 0;
	}

	return false;
}