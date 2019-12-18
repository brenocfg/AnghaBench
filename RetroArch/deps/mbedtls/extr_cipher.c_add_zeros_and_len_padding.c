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

__attribute__((used)) static void add_zeros_and_len_padding( unsigned char *output,
                                       size_t output_len, size_t data_len )
{
    size_t padding_len = output_len - data_len;
    unsigned char i = 0;

    for( i = 1; i < padding_len; i++ )
        output[data_len + i - 1] = 0x00;
    output[output_len - 1] = (unsigned char) padding_len;
}