#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int const d; TYPE_2__* graph; } ;
typedef  TYPE_1__ ccv_nnc_graph_tensor_wraps_ref_t ;
struct TYPE_8__ {struct TYPE_8__* p; TYPE_5__* tensor_wraps_refs; } ;
typedef  TYPE_2__ ccv_nnc_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_t ;
struct TYPE_9__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__* const,TYPE_1__* const,int) ; 

__attribute__((used)) static void _ccv_nnc_graph_deregister_tensor_wraps(ccv_nnc_graph_t* graph, const int tensor_wraps_ref_d)
{
	ccv_nnc_graph_t* p = graph;
	do {
		int i;
		// Remove from the array.
		if (p->tensor_wraps_refs)
			for (i = 0; i < p->tensor_wraps_refs->rnum; i++)
			{
				ccv_nnc_graph_tensor_wraps_ref_t* const tensor_wraps_ref = (ccv_nnc_graph_tensor_wraps_ref_t*)ccv_array_get(p->tensor_wraps_refs, i);
				if (tensor_wraps_ref->d == tensor_wraps_ref_d && tensor_wraps_ref->graph == graph)
				{
					--p->tensor_wraps_refs->rnum;
					if (i < p->tensor_wraps_refs->rnum)
						memcpy(tensor_wraps_ref, tensor_wraps_ref + 1, sizeof(ccv_nnc_graph_exec_t) * (p->tensor_wraps_refs->rnum - i));
					break;
				}
			}
		p = p->p;
	} while (p);
}