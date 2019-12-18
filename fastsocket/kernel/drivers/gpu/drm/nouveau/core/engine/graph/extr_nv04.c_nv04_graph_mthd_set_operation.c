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
typedef  int u32 ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv04_graph_set_ctx1 (struct nouveau_object*,int,int) ; 
 int /*<<< orphan*/  nv04_graph_set_ctx_val (struct nouveau_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nv_ro32 (struct nouveau_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv04_graph_mthd_set_operation(struct nouveau_object *object, u32 mthd,
			      void *args, u32 size)
{
	u32 class = nv_ro32(object, 0) & 0xff;
	u32 data = *(u32 *)args;
	if (data > 5)
		return 1;
	/* Old versions of the objects only accept first three operations. */
	if (data > 2 && class < 0x40)
		return 1;
	nv04_graph_set_ctx1(object, 0x00038000, data << 15);
	/* changing operation changes set of objects needed for validation */
	nv04_graph_set_ctx_val(object, 0, 0);
	return 0;
}