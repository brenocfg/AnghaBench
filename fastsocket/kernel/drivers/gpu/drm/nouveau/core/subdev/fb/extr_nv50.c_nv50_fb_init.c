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
struct nv50_fb_priv {int r100c08; int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_device {int chipset; } ;

/* Variables and functions */
 int nouveau_fb_init (int /*<<< orphan*/ *) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_fb_priv*,int,int) ; 

__attribute__((used)) static int
nv50_fb_init(struct nouveau_object *object)
{
	struct nouveau_device *device = nv_device(object);
	struct nv50_fb_priv *priv = (void *)object;
	int ret;

	ret = nouveau_fb_init(&priv->base);
	if (ret)
		return ret;

	/* Not a clue what this is exactly.  Without pointing it at a
	 * scratch page, VRAM->GART blits with M2MF (as in DDX DFS)
	 * cause IOMMU "read from address 0" errors (rh#561267)
	 */
	nv_wr32(priv, 0x100c08, priv->r100c08 >> 8);

	/* This is needed to get meaningful information from 100c90
	 * on traps. No idea what these values mean exactly. */
	switch (device->chipset) {
	case 0x50:
		nv_wr32(priv, 0x100c90, 0x000707ff);
		break;
	case 0xa3:
	case 0xa5:
	case 0xa8:
		nv_wr32(priv, 0x100c90, 0x000d0fff);
		break;
	case 0xaf:
		nv_wr32(priv, 0x100c90, 0x089d1fff);
		break;
	default:
		nv_wr32(priv, 0x100c90, 0x001d07ff);
		break;
	}

	return 0;
}