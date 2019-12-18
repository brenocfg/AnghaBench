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
typedef  int u32 ;
struct nv50_i2c_port {int addr; } ;
struct nouveau_i2c_port {int dummy; } ;
struct nouveau_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_DBG (char*,...) ; 
 int /*<<< orphan*/  AUX_ERR (char*,int) ; 
 int ENXIO ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  auxch_fini (struct nouveau_i2c*,int) ; 
 int auxch_init (struct nouveau_i2c*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 struct nouveau_i2c* nouveau_i2c (struct nouveau_i2c_port*) ; 
 int nv_mask (struct nouveau_i2c*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_i2c*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_i2c*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
nv94_aux(struct nouveau_i2c_port *base, u8 type, u32 addr, u8 *data, u8 size)
{
	struct nouveau_i2c *aux = nouveau_i2c(base);
	struct nv50_i2c_port *port = (void *)base;
	u32 ctrl, stat, timeout, retries;
	u32 xbuf[4] = {};
	int ch = port->addr;
	int ret, i;

	AUX_DBG("%d: 0x%08x %d\n", type, addr, size);

	ret = auxch_init(aux, ch);
	if (ret)
		goto out;

	stat = nv_rd32(aux, 0x00e4e8 + (ch * 0x50));
	if (!(stat & 0x10000000)) {
		AUX_DBG("sink not detected\n");
		ret = -ENXIO;
		goto out;
	}

	if (!(type & 1)) {
		memcpy(xbuf, data, size);
		for (i = 0; i < 16; i += 4) {
			AUX_DBG("wr 0x%08x\n", xbuf[i / 4]);
			nv_wr32(aux, 0x00e4c0 + (ch * 0x50) + i, xbuf[i / 4]);
		}
	}

	ctrl  = nv_rd32(aux, 0x00e4e4 + (ch * 0x50));
	ctrl &= ~0x0001f0ff;
	ctrl |= type << 12;
	ctrl |= size - 1;
	nv_wr32(aux, 0x00e4e0 + (ch * 0x50), addr);

	/* retry transaction a number of times on failure... */
	ret = -EREMOTEIO;
	for (retries = 0; retries < 32; retries++) {
		/* reset, and delay a while if this is a retry */
		nv_wr32(aux, 0x00e4e4 + (ch * 0x50), 0x80000000 | ctrl);
		nv_wr32(aux, 0x00e4e4 + (ch * 0x50), 0x00000000 | ctrl);
		if (retries)
			udelay(400);

		/* transaction request, wait up to 1ms for it to complete */
		nv_wr32(aux, 0x00e4e4 + (ch * 0x50), 0x00010000 | ctrl);

		timeout = 1000;
		do {
			ctrl = nv_rd32(aux, 0x00e4e4 + (ch * 0x50));
			udelay(1);
			if (!timeout--) {
				AUX_ERR("tx req timeout 0x%08x\n", ctrl);
				goto out;
			}
		} while (ctrl & 0x00010000);

		/* read status, and check if transaction completed ok */
		stat = nv_mask(aux, 0x00e4e8 + (ch * 0x50), 0, 0);
		if (!(stat & 0x000f0f00)) {
			ret = 0;
			break;
		}

		AUX_DBG("%02d 0x%08x 0x%08x\n", retries, ctrl, stat);
	}

	if (type & 1) {
		for (i = 0; i < 16; i += 4) {
			xbuf[i / 4] = nv_rd32(aux, 0x00e4d0 + (ch * 0x50) + i);
			AUX_DBG("rd 0x%08x\n", xbuf[i / 4]);
		}
		memcpy(data, xbuf, size);
	}

out:
	auxch_fini(aux, ch);
	return ret;
}