#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
typedef  TYPE_3__* ccv_cnnp_model_io_t ;
struct TYPE_20__ {int output_size; int input_size; int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * isa; } ;
struct TYPE_22__ {int sequence_size; TYPE_3__** sequence; TYPE_2__ super; } ;
typedef  TYPE_4__ ccv_cnnp_functional_model_t ;
struct TYPE_23__ {int rnum; } ;
typedef  TYPE_5__ ccv_array_t ;
struct TYPE_21__ {scalar_t__ visit; TYPE_17__* model; TYPE_1__* outgoings; TYPE_5__* const incomings; } ;
struct TYPE_19__ {scalar_t__ rnum; } ;
struct TYPE_18__ {scalar_t__ output_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_CNNP_IS_MODEL_INPUT (TYPE_17__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cccalloc (int,int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_5__* const) ; 
 TYPE_3__** ccv_array_get (TYPE_5__* const,int) ; 
 TYPE_5__* ccv_array_new (int,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_5__* const,TYPE_3__* const*) ; 
 int /*<<< orphan*/  ccv_array_resize (TYPE_5__* const,int const) ; 
 int /*<<< orphan*/  ccv_cnnp_functional_model_isa ; 
 int /*<<< orphan*/  memcpy (TYPE_3__**,TYPE_3__* const* const,int) ; 

ccv_cnnp_model_t* ccv_cnnp_model_new(const ccv_cnnp_model_io_t* const inputs, const int input_size, const ccv_cnnp_model_io_t* const outputs, const int output_size)
{
	assert(output_size > 0);
	// Do topological sort.
	ccv_array_t* const reverse_top = ccv_array_new(sizeof(ccv_cnnp_model_io_t), output_size, 0);
	ccv_array_resize(reverse_top, output_size);
	memcpy(ccv_array_get(reverse_top, 0), outputs, sizeof(ccv_cnnp_model_io_t) * output_size);
	// Go from the output, until we meet inputs.
	int i, j, input_count = 0;
	int tensor_output_size = 0; // io can be mapped to multiple tensor outputs, therefore, need to compute the exact tensor output size.
	for (i = 0; i < output_size; i++)
		tensor_output_size += outputs[i]->model->output_size;
	for (i = 0; i < reverse_top->rnum; i++)
	{
		const ccv_cnnp_model_io_t output = *(ccv_cnnp_model_io_t*)ccv_array_get(reverse_top, i);
		assert(!CCV_CNNP_IS_MODEL_INPUT(output->model));
		// If it is input, push it here.
		if (output->incomings)
			for (j = 0; j < output->incomings->rnum; j++)
			{
				const ccv_cnnp_model_io_t input = *(ccv_cnnp_model_io_t*)ccv_array_get(output->incomings, j);
				++input->visit; // Mark it as visited.
				if (input->visit != input->outgoings->rnum) // Not all dependencies visited.
					continue;
				if (!CCV_CNNP_IS_MODEL_INPUT(input->model))
					ccv_array_push(reverse_top, &input);
				else
					++input_count;
			}
	}
	for (i = 0; i < reverse_top->rnum; i++)
	{
		const ccv_cnnp_model_io_t output = *(ccv_cnnp_model_io_t*)ccv_array_get(reverse_top, i);
		output->visit = 0; // Clean the visit back.
	}
	for (i = 0; i < input_size; i++)
		inputs[i]->visit = 0; // Clean the visit back.
	assert(input_count == input_size); // Assuming they all match.
	const int sequence_size = reverse_top->rnum + input_size;
	ccv_cnnp_functional_model_t* const functional_model = (ccv_cnnp_functional_model_t*)cccalloc(1, sizeof(ccv_cnnp_functional_model_t) + sizeof(ccv_cnnp_model_t*) * (sequence_size - 1) + sizeof(ccv_nnc_tensor_symbol_t) * tensor_output_size);
	functional_model->super.isa = &ccv_cnnp_functional_model_isa;
	functional_model->super.outputs = (ccv_nnc_tensor_symbol_t*)(functional_model->sequence + sequence_size);
	functional_model->super.output_size = tensor_output_size;
	functional_model->super.input_size = input_size;
	functional_model->sequence_size = sequence_size;
	memcpy(functional_model->sequence, inputs, sizeof(ccv_cnnp_model_io_t) * input_size);
	for (i = 0; i < reverse_top->rnum; i++)
		functional_model->sequence[input_size + i] = *(ccv_cnnp_model_io_t*)ccv_array_get(reverse_top, reverse_top->rnum - 1 - i);
	ccv_array_free(reverse_top);
	return (ccv_cnnp_model_t*)functional_model;
}