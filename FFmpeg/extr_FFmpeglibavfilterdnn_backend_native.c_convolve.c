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
struct TYPE_3__ {int kernel_size; int input_num; int output_num; float* biases; float const* kernel; int activation; } ;
typedef  TYPE_1__ ConvolutionalParams ;

/* Variables and functions */
 int CLAMP_TO_EDGE (int,int) ; 
 float FFMAX (float,double) ; 
#define  RELU 130 
#define  SIGMOID 129 
#define  TANH 128 
 int /*<<< orphan*/  exp (float) ; 

__attribute__((used)) static void convolve(const float *input, float *output, const ConvolutionalParams *conv_params, int width, int height)
{
    int y, x, n_filter, ch, kernel_y, kernel_x;
    int radius = conv_params->kernel_size >> 1;
    int src_linesize = width * conv_params->input_num;
    int filter_linesize = conv_params->kernel_size * conv_params->input_num;
    int filter_size = conv_params->kernel_size * filter_linesize;

    for (y = 0; y < height; ++y){
        for (x = 0; x < width; ++x){
            for (n_filter = 0; n_filter < conv_params->output_num; ++n_filter){
                output[n_filter] = conv_params->biases[n_filter];
                for (ch = 0; ch < conv_params->input_num; ++ch){
                    for (kernel_y = 0; kernel_y < conv_params->kernel_size; ++kernel_y){
                        for (kernel_x = 0; kernel_x < conv_params->kernel_size; ++kernel_x){
                            output[n_filter] += input[CLAMP_TO_EDGE(y + kernel_y - radius, height) * src_linesize +
                                                      CLAMP_TO_EDGE(x + kernel_x - radius, width) * conv_params->input_num + ch] *
                                                conv_params->kernel[n_filter * filter_size + kernel_y * filter_linesize +
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
                }
            }
            output += conv_params->output_num;
        }
    }
}