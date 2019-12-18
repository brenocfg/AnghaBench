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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_mem_exec_func {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ type; int ranks; } ;
struct nouveau_fb {TYPE_1__ ram; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NV_MEM_TYPE_GDDR5 ; 
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_device*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mclk_mrs(struct nouveau_mem_exec_func *exec, int mr, u32 data)
{
	struct nouveau_device *device = nouveau_dev(exec->dev);
	struct nouveau_fb *pfb = nouveau_fb(device);
	if (pfb->ram.type != NV_MEM_TYPE_GDDR5) {
		if (mr <= 1) {
			nv_wr32(device, 0x10f300 + ((mr - 0) * 4), data);
			if (pfb->ram.ranks > 1)
				nv_wr32(device, 0x10f308 + ((mr - 0) * 4), data);
		} else
		if (mr <= 3) {
			nv_wr32(device, 0x10f320 + ((mr - 2) * 4), data);
			if (pfb->ram.ranks > 1)
				nv_wr32(device, 0x10f328 + ((mr - 2) * 4), data);
		}
	} else {
		if      (mr ==  0) nv_wr32(device, 0x10f300 + (mr * 4), data);
		else if (mr <=  7) nv_wr32(device, 0x10f32c + (mr * 4), data);
		else if (mr == 15) nv_wr32(device, 0x10f34c, data);
	}
}