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
struct TYPE_6__ {int kernel_size; int input_num; scalar_t__ padding_method; int dilation; int output_num; float* biases; float* kernel; int activation; scalar_t__ has_bias; } ;
struct TYPE_5__ {int* dims; float* data; int /*<<< orphan*/  length; int /*<<< orphan*/  data_type; } ;
typedef  TYPE_1__ DnnOperand ;
typedef  TYPE_2__ ConvolutionalParams ;

/* Variables and functions */
 int CLAMP_TO_EDGE (int,int) ; 
 float FFMAX (float,double) ; 
 double FFMIN (float,double) ; 
#define  LEAKY_RELU 132 
#define  NONE 131 
#define  RELU 130 
 scalar_t__ SAME_CLAMP_TO_EDGE ; 
#define  SIGMOID 129 
#define  TANH 128 
 scalar_t__ VALID ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 float* av_realloc (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_operand_data_length (TYPE_1__*) ; 
 int /*<<< orphan*/  exp (float) ; 

int dnn_execute_layer_conv2d(DnnOperand *operands, const int32_t *input_operand_indexes,
                             int32_t output_operand_index, const void *parameters)
{
    float *output;
    int32_t input_operand_index = input_operand_indexes[0];
    int number = operands[input_operand_index].dims[0];
    int height = operands[input_operand_index].dims[1];
    int width = operands[input_operand_index].dims[2];
    int channel = operands[input_operand_index].dims[3];
    const float *input = operands[input_operand_index].data;
    const ConvolutionalParams *conv_params = (const ConvolutionalParams *)parameters;

    int radius = conv_params->kernel_size >> 1;
    int src_linesize = width * conv_params->input_num;
    int filter_linesize = conv_params->kernel_size * conv_params->input_num;
    int filter_size = conv_params->kernel_size * filter_linesize;
    int pad_size = (conv_params->padding_method == VALID) ? (conv_params->kernel_size - 1) / 2 * conv_params->dilation : 0;

    DnnOperand *output_operand = &operands[output_operand_index];
    output_operand->dims[0] = number;
    output_operand->dims[1] = height - pad_size * 2;
    output_operand->dims[2] = width - pad_size * 2;
    output_operand->dims[3] = conv_params->output_num;
    output_operand->data_type = operands[input_operand_index].data_type;
    output_operand->length = calculate_operand_data_length(output_operand);
    output_operand->data = av_realloc(output_operand->data, output_operand->length);
    if (!output_operand->data)
        return -1;
    output = output_operand->data;

    av_assert0(channel == conv_params->input_num);

    for (int y = pad_size; y < height - pad_size; ++y) {
        for (int x = pad_size; x < width - pad_size; ++x) {
            for (int n_filter = 0; n_filter < conv_params->output_num; ++n_filter) {
                if (conv_params->has_bias)
                    output[n_filter] = conv_params->biases[n_filter];
                else
                    output[n_filter] = 0.f;

                for (int ch = 0; ch < conv_params->input_num; ++ch) {
                    for (int kernel_y = 0; kernel_y < conv_params->kernel_size; ++kernel_y) {
                        for (int kernel_x = 0; kernel_x < conv_params->kernel_size; ++kernel_x) {
                            float input_pel;
                            if (conv_params->padding_method == SAME_CLAMP_TO_EDGE) {
                                int y_pos = CLAMP_TO_EDGE(y + (kernel_y - radius) * conv_params->dilation, height);
                                int x_pos = CLAMP_TO_EDGE(x + (kernel_x - radius) * conv_params->dilation, width);
                                input_pel = input[y_pos * src_linesize + x_pos * conv_params->input_num + ch];
                            } else {
                                int y_pos = y + (kernel_y - radius) * conv_params->dilation;
                                int x_pos = x + (kernel_x - radius) * conv_params->dilation;
                                input_pel = (x_pos < 0 || x_pos >= width || y_pos < 0 || y_pos >= height) ? 0.0 :
                                                   input[y_pos * src_linesize + x_pos * conv_params->input_num + ch];
                            }


                            output[n_filter] += input_pel * conv_params->kernel[n_filter * filter_size + kernel_y * filter_linesize +
                                                                                kernel_x * conv_params->input_num + ch];
                        }
                    }
                }
                switch (conv_params->activation){
                case RELU:
                    output[n_filter] = FFMAX(output[n_filter], 0.0);
                    break;
                case TANH:
                    output[n_filter] = 2.0f  / (1.0f + exp(-2.0f * output[n_filter])) - 1.0f;
                    break;
                case SIGMOID:
                    output[n_filter] = 1.0f / (1.0f + exp(-output[n_filter]));
                    break;
                case NONE:
                    break;
                case LEAKY_RELU:
                    output[n_filter] = FFMAX(output[n_filter], 0.0) + 0.2 * FFMIN(output[n_filter], 0.0);
                }
            }
            output += conv_params->output_num;
        }
    }
    return 0;
}