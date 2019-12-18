#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  y; } ;
struct TYPE_9__ {TYPE_1__ val; } ;
struct TYPE_8__ {float* data; int /*<<< orphan*/  length; int /*<<< orphan*/  data_type; int /*<<< orphan*/ * dims; } ;
typedef  TYPE_2__ DnnOperand ;
typedef  TYPE_3__ DnnLayerMaximumParams ;

/* Variables and functions */
 int DNN_ERROR ; 
 float FFMAX (float const,int /*<<< orphan*/ ) ; 
 float* av_realloc (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_operand_data_length (TYPE_2__*) ; 
 int calculate_operand_dims_count (TYPE_2__*) ; 

int dnn_execute_layer_maximum(DnnOperand *operands, const int32_t *input_operand_indexes,
                              int32_t output_operand_index, const void *parameters)
{
    const DnnOperand *input = &operands[input_operand_indexes[0]];
    DnnOperand *output = &operands[output_operand_index];
    const DnnLayerMaximumParams *params = (const DnnLayerMaximumParams *)parameters;
    int dims_count;
    const float *src;
    float *dst;

    for (int i = 0; i < 4; ++i)
        output->dims[i] = input->dims[i];

    output->data_type = input->data_type;
    output->length = calculate_operand_data_length(output);
    output->data = av_realloc(output->data, output->length);
    if (!output->data)
        return DNN_ERROR;

    dims_count = calculate_operand_dims_count(output);
    src = input->data;
    dst = output->data;
    for (int i = 0; i < dims_count; ++i)
        dst[i] = FFMAX(src[i], params->val.y);

    return 0;
}