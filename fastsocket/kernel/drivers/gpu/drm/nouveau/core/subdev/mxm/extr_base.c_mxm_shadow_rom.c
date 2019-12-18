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
struct nouveau_mxm {int* mxms; } ;
struct nouveau_i2c_port {int dummy; } ;
struct nouveau_i2c {struct nouveau_i2c_port* (* find ) (struct nouveau_i2c*,int) ;} ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mxm_ddc_map (struct nouveau_bios*,int) ; 
 scalar_t__ mxm_shadow_rom_fetch (struct nouveau_i2c_port*,int,int /*<<< orphan*/ ,int,int*) ; 
 int mxms_headerlen (struct nouveau_mxm*) ; 
 int mxms_structlen (struct nouveau_mxm*) ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_mxm*) ; 
 struct nouveau_i2c* nouveau_i2c (struct nouveau_mxm*) ; 
 struct nouveau_i2c_port* stub1 (struct nouveau_i2c*,int) ; 

__attribute__((used)) static bool
mxm_shadow_rom(struct nouveau_mxm *mxm, u8 version)
{
	struct nouveau_bios *bios = nouveau_bios(mxm);
	struct nouveau_i2c *i2c = nouveau_i2c(mxm);
	struct nouveau_i2c_port *port = NULL;
	u8 i2cidx, mxms[6], addr, size;

	i2cidx = mxm_ddc_map(bios, 1 /* LVDS_DDC */) & 0x0f;
	if (i2cidx < 0x0f)
		port = i2c->find(i2c, i2cidx);
	if (!port)
		return false;

	addr = 0x54;
	if (!mxm_shadow_rom_fetch(port, addr, 0, 6, mxms)) {
		addr = 0x56;
		if (!mxm_shadow_rom_fetch(port, addr, 0, 6, mxms))
			return false;
	}

	mxm->mxms = mxms;
	size = mxms_headerlen(mxm) + mxms_structlen(mxm);
	mxm->mxms = kmalloc(size, GFP_KERNEL);

	if (mxm->mxms &&
	    mxm_shadow_rom_fetch(port, addr, 0, size, mxm->mxms))
		return true;

	kfree(mxm->mxms);
	mxm->mxms = NULL;
	return false;
}