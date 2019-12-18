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
typedef  scalar_t__ u32 ;
struct nouveau_ramht {int dummy; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nouveau_bar* nouveau_bar (struct nouveau_ramht*) ; 
 scalar_t__ nouveau_ramht_hash (struct nouveau_ramht*,int,scalar_t__) ; 
 TYPE_1__* nv_gpuobj (struct nouveau_ramht*) ; 
 int /*<<< orphan*/  nv_ro32 (struct nouveau_ramht*,scalar_t__) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_ramht*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 

int
nouveau_ramht_insert(struct nouveau_ramht *ramht, int chid,
		     u32 handle, u32 context)
{
	struct nouveau_bar *bar = nouveau_bar(ramht);
	u32 co, ho;

	co = ho = nouveau_ramht_hash(ramht, chid, handle);
	do {
		if (!nv_ro32(ramht, co + 4)) {
			nv_wo32(ramht, co + 0, handle);
			nv_wo32(ramht, co + 4, context);
			if (bar)
				bar->flush(bar);
			return co;
		}

		co += 8;
		if (co >= nv_gpuobj(ramht)->size)
			co = 0;
	} while (co != ho);

	return -ENOMEM;
}