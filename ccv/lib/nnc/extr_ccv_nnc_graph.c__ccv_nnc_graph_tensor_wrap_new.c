#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_multiview_t ;
struct TYPE_3__ {int count; int /*<<< orphan*/ ** tensors; scalar_t__ index; scalar_t__ update_required; } ;
typedef  TYPE_1__ ccv_nnc_graph_tensor_wrap_t ;

/* Variables and functions */
 int _ccv_nnc_tensor_multiview_level_count (int /*<<< orphan*/  const* const) ; 
 scalar_t__ ccmalloc (int) ; 

__attribute__((used)) static ccv_nnc_graph_tensor_wrap_t* _ccv_nnc_graph_tensor_wrap_new(const ccv_nnc_tensor_multiview_t* const mv)
{
	const int level_count = _ccv_nnc_tensor_multiview_level_count(mv);
	ccv_nnc_graph_tensor_wrap_t* tensor_wrap = (ccv_nnc_graph_tensor_wrap_t*)ccmalloc(sizeof(ccv_nnc_graph_tensor_wrap_t) + sizeof(ccv_nnc_tensor_t*) * (level_count - 1));
	tensor_wrap->update_required = 0;
	tensor_wrap->count = level_count;
	tensor_wrap->index = 0;
	tensor_wrap->tensors[0] = (ccv_nnc_tensor_t*)mv;
	return tensor_wrap;
}