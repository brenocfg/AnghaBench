#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int* inc; } ;
typedef  TYPE_3__ ccv_nnc_tensor_view_t ;
struct TYPE_8__ {int* dim; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  u8; } ;
struct TYPE_10__ {TYPE_2__ info; int /*<<< orphan*/  type; TYPE_1__ data; } ;
typedef  TYPE_4__ ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int const CCV_GET_DATA_TYPE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_GET_TAPE_ALLOC (int /*<<< orphan*/ ) ; 
 int CCV_IS_TENSOR_VIEW (TYPE_4__ const* const) ; 
 int const CCV_NNC_LONG_DOT_GRAPH ; 
 int CCV_NNC_MAX_DIM_ALLOC ; 
 int CCV_TENSOR_GET_DEVICE_ID (int /*<<< orphan*/ ) ; 
 int const ccv_nnc_dimension_count (int const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_graph_dot_tensor(const int index, const ccv_nnc_tensor_t* const tensor, const int zone, const int flags, const int depth, FILE* out)
{
	// if it has an alias pointer, or, it is a long form.
	if (flags == CCV_NNC_LONG_DOT_GRAPH)
		fputc('{', out);
	const int is_tensor_view = CCV_IS_TENSOR_VIEW(tensor);
	if (is_tensor_view)
		fprintf(out, "tensorview%d", index);
	else
		fprintf(out, "tensor%d", index);
	int i;
	for (i = 0; i < depth; i++) // Print subscription to denote depth.
		fputc('\'', out);
	if (CCV_GET_TAPE_ALLOC(tensor->type))
		fputs(" (t)", out);
	if (flags == CCV_NNC_LONG_DOT_GRAPH)
	{
		const int device_id = CCV_TENSOR_GET_DEVICE_ID(tensor->info.type);
		fprintf(out, "|d%d|zone%d", device_id, zone);
		for (i = 0; i < depth; i++) // Print subscription to denote depth.
			fputc('\'', out);
		uintptr_t aptr = (uintptr_t)tensor->data.u8;
		const int* ainc = is_tensor_view ? ((ccv_nnc_tensor_view_t*)(tensor))->inc : tensor->info.dim;
		// For the last one, we don't extend to full ainc.
		size_t ainc_size = (ccv_nnc_dimension_count(ainc) - ainc[0] + tensor->info.dim[0]) * CCV_GET_DATA_TYPE_SIZE(tensor->type);
		// Print out the range as well.
		fprintf(out, "|{%#010x|%#010x}|%d", (uint32_t)aptr, (uint32_t)(aptr + ainc_size - 1), tensor->info.dim[0]);
		for (i = 1; i < CCV_NNC_MAX_DIM_ALLOC && tensor->info.dim[i]; i++)
			fprintf(out, "x%d", tensor->info.dim[i]);
		fputc('}', out);
	}
}