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
struct nv50_disp_priv {int dummy; } ;
struct TYPE_2__ {int chid; } ;
struct nv50_disp_pioc {TYPE_1__ base; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int EBUSY ; 
 int nv50_disp_chan_fini (TYPE_1__*,int) ; 
 int /*<<< orphan*/  nv_error (struct nv50_disp_pioc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_mask (struct nv50_disp_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_rd32 (struct nv50_disp_priv*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nv50_disp_priv*,int,int,int) ; 

__attribute__((used)) static int
nvd0_disp_pioc_fini(struct nouveau_object *object, bool suspend)
{
	struct nv50_disp_priv *priv = (void *)object->engine;
	struct nv50_disp_pioc *pioc = (void *)object;
	int chid = pioc->base.chid;

	nv_mask(priv, 0x610490 + (chid * 0x10), 0x00000001, 0x00000000);
	if (!nv_wait(priv, 0x610490 + (chid * 0x10), 0x00030000, 0x00000000)) {
		nv_error(pioc, "timeout: 0x%08x\n",
			 nv_rd32(priv, 0x610490 + (chid * 0x10)));
		if (suspend)
			return -EBUSY;
	}

	/* disable error reporting */
	nv_mask(priv, 0x610090, 0x00000001 << chid, 0x00000000);
	nv_mask(priv, 0x6100a0, 0x00000001 << chid, 0x00000000);

	return nv50_disp_chan_fini(&pioc->base, suspend);
}