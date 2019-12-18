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
struct nouveau_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_ERR (char*,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  auxch_fini (struct nouveau_i2c*,int) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_i2c*,int,int,int const) ; 
 int nv_rd32 (struct nouveau_i2c*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
auxch_init(struct nouveau_i2c *aux, int ch)
{
	const u32 unksel = 1; /* nfi which to use, or if it matters.. */
	const u32 ureq = unksel ? 0x00100000 : 0x00200000;
	const u32 urep = unksel ? 0x01000000 : 0x02000000;
	u32 ctrl, timeout;

	/* wait up to 1ms for any previous transaction to be done... */
	timeout = 1000;
	do {
		ctrl = nv_rd32(aux, 0x00e4e4 + (ch * 0x50));
		udelay(1);
		if (!timeout--) {
			AUX_ERR("begin idle timeout 0x%08x\n", ctrl);
			return -EBUSY;
		}
	} while (ctrl & 0x03010000);

	/* set some magic, and wait up to 1ms for it to appear */
	nv_mask(aux, 0x00e4e4 + (ch * 0x50), 0x00300000, ureq);
	timeout = 1000;
	do {
		ctrl = nv_rd32(aux, 0x00e4e4 + (ch * 0x50));
		udelay(1);
		if (!timeout--) {
			AUX_ERR("magic wait 0x%08x\n", ctrl);
			auxch_fini(aux, ch);
			return -EBUSY;
		}
	} while ((ctrl & 0x03000000) != urep);

	return 0;
}