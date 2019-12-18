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
struct nv50_mpeg_priv {int dummy; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_info (struct nv50_mpeg_priv*,char*,int,int,int,int) ; 
 int nv_rd32 (struct nv50_mpeg_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_mpeg_priv*,int,int) ; 

void
nv50_mpeg_intr(struct nouveau_subdev *subdev)
{
	struct nv50_mpeg_priv *priv = (void *)subdev;
	u32 stat = nv_rd32(priv, 0x00b100);
	u32 type = nv_rd32(priv, 0x00b230);
	u32 mthd = nv_rd32(priv, 0x00b234);
	u32 data = nv_rd32(priv, 0x00b238);
	u32 show = stat;

	if (stat & 0x01000000) {
		/* happens on initial binding of the object */
		if (type == 0x00000020 && mthd == 0x0000) {
			nv_wr32(priv, 0x00b308, 0x00000100);
			show &= ~0x01000000;
		}
	}

	if (show) {
		nv_info(priv, "0x%08x 0x%08x 0x%08x 0x%08x\n",
			stat, type, mthd, data);
	}

	nv_wr32(priv, 0x00b100, stat);
	nv_wr32(priv, 0x00b230, 0x00000001);
}