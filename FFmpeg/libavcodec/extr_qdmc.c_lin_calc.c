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
struct TYPE_3__ {int subframe_size; float* noise_buffer; float* noise2_buffer; } ;
typedef  TYPE_1__ QDMCContext ;

/* Variables and functions */

__attribute__((used)) static void lin_calc(QDMCContext *s, float amplitude, int node1, int node2, int index)
{
    int subframe_size, i, j, k, length;
    float scale, *noise_ptr;

    scale = 0.5 * amplitude;
    subframe_size = s->subframe_size;
    if (subframe_size >= node2)
        subframe_size = node2;
    length = (subframe_size - node1) & 0xFFFC;
    j = node1;
    noise_ptr = &s->noise_buffer[256 * index];

    for (i = 0; i < length; i += 4, j+= 4, noise_ptr += 4) {
        s->noise2_buffer[j    ] += scale * noise_ptr[0];
        s->noise2_buffer[j + 1] += scale * noise_ptr[1];
        s->noise2_buffer[j + 2] += scale * noise_ptr[2];
        s->noise2_buffer[j + 3] += scale * noise_ptr[3];
    }

    k = length + node1;
    noise_ptr = s->noise_buffer + length + (index << 8);
    for (i = length; i < subframe_size - node1; i++, k++, noise_ptr++)
        s->noise2_buffer[k] += scale * noise_ptr[0];
}