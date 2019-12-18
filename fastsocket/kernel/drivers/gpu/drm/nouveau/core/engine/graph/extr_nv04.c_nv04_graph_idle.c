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
struct nouveau_graph {int dummy; } ;
struct TYPE_2__ {scalar_t__ card_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PGRAPH_STATUS ; 
 int NV40_PGRAPH_STATUS_SYNC_STALL ; 
 scalar_t__ NV_40 ; 
 struct nouveau_graph* nouveau_graph (void*) ; 
 TYPE_1__* nv_device (void*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_graph*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_rd32 (struct nouveau_graph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wait (struct nouveau_graph*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool
nv04_graph_idle(void *obj)
{
	struct nouveau_graph *graph = nouveau_graph(obj);
	u32 mask = 0xffffffff;

	if (nv_device(obj)->card_type == NV_40)
		mask &= ~NV40_PGRAPH_STATUS_SYNC_STALL;

	if (!nv_wait(graph, NV04_PGRAPH_STATUS, mask, 0)) {
		nv_error(graph, "idle timed out with status 0x%08x\n",
			 nv_rd32(graph, NV04_PGRAPH_STATUS));
		return false;
	}

	return true;
}