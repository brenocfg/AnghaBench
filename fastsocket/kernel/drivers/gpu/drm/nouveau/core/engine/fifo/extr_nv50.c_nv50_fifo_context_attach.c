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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct nv50_fifo_base {int /*<<< orphan*/  eng; } ;
struct nouveau_object {int /*<<< orphan*/  engine; scalar_t__ parent; } ;
struct nouveau_gpuobj {scalar_t__ addr; scalar_t__ size; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;
struct TYPE_4__ {int addr; } ;
struct TYPE_3__ {int addr; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVDEV_ENGINE_GR 130 
#define  NVDEV_ENGINE_MPEG 129 
#define  NVDEV_ENGINE_SW 128 
 int lower_32_bits (scalar_t__) ; 
 struct nouveau_bar* nouveau_bar (struct nouveau_object*) ; 
 TYPE_2__* nv_engctx (struct nouveau_gpuobj*) ; 
 int nv_engidx (int /*<<< orphan*/ ) ; 
 TYPE_1__* nv_gpuobj (struct nv50_fifo_base*) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int
nv50_fifo_context_attach(struct nouveau_object *parent,
			 struct nouveau_object *object)
{
	struct nouveau_bar *bar = nouveau_bar(parent);
	struct nv50_fifo_base *base = (void *)parent->parent;
	struct nouveau_gpuobj *ectx = (void *)object;
	u64 limit = ectx->addr + ectx->size - 1;
	u64 start = ectx->addr;
	u32 addr;

	switch (nv_engidx(object->engine)) {
	case NVDEV_ENGINE_SW   : return 0;
	case NVDEV_ENGINE_GR   : addr = 0x0000; break;
	case NVDEV_ENGINE_MPEG : addr = 0x0060; break;
	default:
		return -EINVAL;
	}

	nv_engctx(ectx)->addr = nv_gpuobj(base)->addr >> 12;
	nv_wo32(base->eng, addr + 0x00, 0x00190000);
	nv_wo32(base->eng, addr + 0x04, lower_32_bits(limit));
	nv_wo32(base->eng, addr + 0x08, lower_32_bits(start));
	nv_wo32(base->eng, addr + 0x0c, upper_32_bits(limit) << 24 |
					upper_32_bits(start));
	nv_wo32(base->eng, addr + 0x10, 0x00000000);
	nv_wo32(base->eng, addr + 0x14, 0x00000000);
	bar->flush(bar);
	return 0;
}