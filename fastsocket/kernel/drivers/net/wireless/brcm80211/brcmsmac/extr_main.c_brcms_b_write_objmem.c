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
typedef  int uint ;
typedef  int u32 ;
typedef  int u16 ;
struct brcms_hardware {struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_read32 (struct bcma_device*,int) ; 
 int /*<<< orphan*/  bcma_wflush16 (struct bcma_device*,int,int) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int,int) ; 
 int /*<<< orphan*/  objaddr ; 
 int /*<<< orphan*/  objdata ; 

__attribute__((used)) static void
brcms_b_write_objmem(struct brcms_hardware *wlc_hw, uint offset, u16 v,
		     u32 sel)
{
	struct bcma_device *core = wlc_hw->d11core;
	u16 objoff = D11REGOFFS(objdata);

	bcma_write32(core, D11REGOFFS(objaddr), sel | (offset >> 2));
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	if (offset & 2)
		objoff += 2;

	bcma_wflush16(core, objoff, v);
}