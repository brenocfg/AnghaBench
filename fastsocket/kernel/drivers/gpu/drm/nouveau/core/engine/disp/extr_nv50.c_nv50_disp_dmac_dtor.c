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
struct nv50_disp_dmac {int /*<<< orphan*/  base; int /*<<< orphan*/  pushdma; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,struct nouveau_object**) ; 
 int /*<<< orphan*/  nv50_disp_chan_destroy (int /*<<< orphan*/ *) ; 

void
nv50_disp_dmac_dtor(struct nouveau_object *object)
{
	struct nv50_disp_dmac *dmac = (void *)object;
	nouveau_object_ref(NULL, (struct nouveau_object **)&dmac->pushdma);
	nv50_disp_chan_destroy(&dmac->base);
}