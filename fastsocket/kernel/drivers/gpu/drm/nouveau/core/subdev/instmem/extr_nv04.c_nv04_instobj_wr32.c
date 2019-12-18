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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nv04_instobj_priv {TYPE_1__* mem; } ;
struct nouveau_object {int /*<<< orphan*/  engine; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv04_instobj_wr32(struct nouveau_object *object, u64 addr, u32 data)
{
	struct nv04_instobj_priv *node = (void *)object;
	nv_wo32(object->engine, node->mem->offset + addr, data);
}