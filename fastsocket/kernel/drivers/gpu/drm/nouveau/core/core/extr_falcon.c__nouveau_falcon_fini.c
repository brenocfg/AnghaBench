#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
struct nouveau_falcon {int /*<<< orphan*/  base; TYPE_2__ code; TYPE_1__ data; scalar_t__ external; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int nouveau_engine_fini (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_mo32 (struct nouveau_falcon*,int,int,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_falcon*,int,int) ; 

int
_nouveau_falcon_fini(struct nouveau_object *object, bool suspend)
{
	struct nouveau_falcon *falcon = (void *)object;

	if (!suspend) {
		nouveau_gpuobj_ref(NULL, &falcon->core);
		if (falcon->external) {
			kfree(falcon->data.data);
			kfree(falcon->code.data);
			falcon->code.data = NULL;
		}
	}

	nv_mo32(falcon, 0x048, 0x00000003, 0x00000000);
	nv_wo32(falcon, 0x014, 0xffffffff);

	return nouveau_engine_fini(&falcon->base, suspend);
}