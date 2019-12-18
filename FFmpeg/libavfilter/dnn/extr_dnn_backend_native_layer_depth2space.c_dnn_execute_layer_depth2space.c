#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_6__ {int block_size; } ;
struct TYPE_5__ {int* dims; float* data; int /*<<< orphan*/  length; int /*<<< orphan*/  data_type; } ;
typedef  TYPE_1__ DnnOperand ;
typedef  TYPE_2__ DepthToSpaceParams ;

/* Variables and functions */
 float* av_realloc (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_operand_data_length (TYPE_1__*) ; 

int dnn_execute_layer_depth2space(DnnOperand *operands, const int32_t *input_operand_indexes,
                                  int32_t output_operand_index, const void *parameters)
{
    float *output;
    const DepthToSpaceParams *params = (const DepthToSpaceParams *)parameters;
    int block_size = params->block_size;
    int32_t input_operand_index = input_operand_indexes[0];
    int number = operands[input_operand_index].dims[0];
    int height = operands[input_operand_index].dims[1];
    int width = operands[input_operand_index].dims[2];
    int channels = operands[input_operand_index].dims[3];
    const float *input = operands[input_operand_index].data;

    int y, x, by, bx, ch;
    int new_channels = channels / (block_size * block_size);
    int output_linesize = width * channels;
    int by_linesize = output_linesize / block_size;
    int x_linesize = new_channels * block_size;

    DnnOperand *output_operand = &operands[output_operand_index];
    output_operand->dims[0] = number;
    output_operand->dims[1] = height * block_size;
    output_operand->dims[2] = width * block_size;
    output_operand->dims[3] = new_channels;
    output_operand->data_type = operands[input_operand_index].data_type;
    output_operand->length = calculate_operand_data_length(output_operand);
    output_operand->data = av_realloc(output_operand->data, output_operand->length);
    if (!output_operand->data)
        return -1;
    output = output_operand->data;

    for (y = 0; y < height; ++y){
        for (x = 0; x < width; ++x){
            for (by = 0; by < block_size; ++by){
                for (bx = 0; bx < block_size; ++bx){
                    for (ch = 0; ch < new_channels; ++ch){
                        output[by * by_linesize + x * x_linesize + bx * new_channels + ch] = input[ch];
                    }
                    input += new_channels;
                }
            }
        }
        output += output_linesize;
    }
    return 0;
}