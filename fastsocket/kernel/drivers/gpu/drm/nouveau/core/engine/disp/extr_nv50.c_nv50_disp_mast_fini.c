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
struct nv50_disp_priv {int dummy; } ;
struct nv50_disp_dmac {int /*<<< orphan*/  base; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int EBUSY ; 
 int nv50_disp_chan_fini (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_error (struct nv50_disp_dmac*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_mask (struct nv50_disp_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_rd32 (struct nv50_disp_priv*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nv50_disp_priv*,int,int,int) ; 

__attribute__((used)) static int
nv50_disp_mast_fini(struct nouveau_object *object, bool suspend)
{
	struct nv50_disp_priv *priv = (void *)object->engine;
	struct nv50_disp_dmac *mast = (void *)object;

	/* deactivate channel */
	nv_mask(priv, 0x610200, 0x00000010, 0x00000000);
	nv_mask(priv, 0x610200, 0x00000003, 0x00000000);
	if (!nv_wait(priv, 0x610200, 0x001e0000, 0x00000000)) {
		nv_error(mast, "fini: 0x%08x\n", nv_rd32(priv, 0x610200));
		if (suspend)
			return -EBUSY;
	}

	/* disable error reporting */
	nv_mask(priv, 0x610028, 0x00010001, 0x00000000);

	return nv50_disp_chan_fini(&mast->base, suspend);
}