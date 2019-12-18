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
typedef  int u32 ;
struct nouveau_subdev {int dummy; } ;
struct nouveau_bus {int dummy; } ;

/* Variables and functions */
 struct nouveau_bus* nouveau_bus (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_bus*,char*,...) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_bus*,int,int,int) ; 
 int nv_rd32 (struct nouveau_bus*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_bus*,int,int) ; 

__attribute__((used)) static void
nvc0_bus_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_bus *pbus = nouveau_bus(subdev);
	u32 stat = nv_rd32(pbus, 0x001100) & nv_rd32(pbus, 0x001140);

	if (stat & 0x0000000e) {
		u32 addr = nv_rd32(pbus, 0x009084);
		u32 data = nv_rd32(pbus, 0x009088);

		nv_error(pbus, "MMIO %s of 0x%08x FAULT at 0x%06x [ %s%s%s]\n",
			 (addr & 0x00000002) ? "write" : "read", data,
			 (addr & 0x00fffffc),
			 (stat & 0x00000002) ? "!ENGINE " : "",
			 (stat & 0x00000004) ? "IBUS " : "",
			 (stat & 0x00000008) ? "TIMEOUT " : "");

		nv_wr32(pbus, 0x009084, 0x00000000);
		nv_wr32(pbus, 0x001100, (stat & 0x0000000e));
		stat &= ~0x0000000e;
	}

	if (stat) {
		nv_error(pbus, "unknown intr 0x%08x\n", stat);
		nv_mask(pbus, 0x001140, stat, 0x00000000);
	}
}