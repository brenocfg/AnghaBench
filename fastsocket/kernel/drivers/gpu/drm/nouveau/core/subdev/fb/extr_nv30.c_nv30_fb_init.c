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
struct nv30_fb_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_device {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_ref (struct nv30_fb_priv*,int,int,int) ; 
 int nouveau_fb_init (int /*<<< orphan*/ *) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 int nv_rd32 (struct nv30_fb_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv30_fb_priv*,int,int /*<<< orphan*/ ) ; 

int
nv30_fb_init(struct nouveau_object *object)
{
	struct nouveau_device *device = nv_device(object);
	struct nv30_fb_priv *priv = (void *)object;
	int ret, i, j;

	ret = nouveau_fb_init(&priv->base);
	if (ret)
		return ret;

	/* Init the memory timing regs at 0x10037c/0x1003ac */
	if (device->chipset == 0x30 ||
	    device->chipset == 0x31 ||
	    device->chipset == 0x35) {
		/* Related to ROP count */
		int n = (device->chipset == 0x31 ? 2 : 4);
		int l = nv_rd32(priv, 0x1003d0);

		for (i = 0; i < n; i++) {
			for (j = 0; j < 3; j++)
				nv_wr32(priv, 0x10037c + 0xc * i + 0x4 * j,
					calc_ref(priv, l, 0, j));

			for (j = 0; j < 2; j++)
				nv_wr32(priv, 0x1003ac + 0x8 * i + 0x4 * j,
					calc_ref(priv, l, 1, j));
		}
	}

	return 0;
}