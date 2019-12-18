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
struct nv04_fb_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFB_CFG0 ; 
 int nouveau_fb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_fb_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv04_fb_init(struct nouveau_object *object)
{
	struct nv04_fb_priv *priv = (void *)object;
	int ret;

	ret = nouveau_fb_init(&priv->base);
	if (ret)
		return ret;

	/* This is what the DDX did for NV_ARCH_04, but a mmio-trace shows
	 * nvidia reading PFB_CFG_0, then writing back its original value.
	 * (which was 0x701114 in this case)
	 */
	nv_wr32(priv, NV04_PFB_CFG0, 0x1114);
	return 0;
}