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
typedef  int u32 ;
struct TYPE_2__ {int post; } ;
struct nv04_devinit_priv {TYPE_1__ base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_devinit_init (TYPE_1__*) ; 
 int /*<<< orphan*/  nv_info (struct nv04_devinit_priv*,char*) ; 
 int nv_rdvgac (struct nv04_devinit_priv*,int /*<<< orphan*/ ,int) ; 

int
nv04_devinit_init(struct nouveau_object *object)
{
	struct nv04_devinit_priv *priv = (void *)object;

	if (!priv->base.post) {
		u32 htotal = nv_rdvgac(priv, 0, 0x06);
		htotal |= (nv_rdvgac(priv, 0, 0x07) & 0x01) << 8;
		htotal |= (nv_rdvgac(priv, 0, 0x07) & 0x20) << 4;
		htotal |= (nv_rdvgac(priv, 0, 0x25) & 0x01) << 10;
		htotal |= (nv_rdvgac(priv, 0, 0x41) & 0x01) << 11;
		if (!htotal) {
			nv_info(priv, "adaptor not initialised\n");
			priv->base.post = true;
		}
	}

	return nouveau_devinit_init(&priv->base);
}