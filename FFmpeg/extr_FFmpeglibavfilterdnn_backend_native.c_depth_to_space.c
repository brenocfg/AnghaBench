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

/* Variables and functions */

__attribute__((used)) static void depth_to_space(const float *input, float *output, int block_size, int width, int height, int channels)
{
    int y, x, by, bx, ch;
    int new_channels = channels / (block_size * block_size);
    int output_linesize = width * channels;
    int by_linesize = output_linesize / block_size;
    int x_linesize = new_channels * block_size;

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
}