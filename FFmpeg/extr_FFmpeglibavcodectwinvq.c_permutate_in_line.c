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
typedef  int uint8_t ;
typedef  int int16_t ;
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;

/* Variables and functions */
 int TWINVQ_FT_LONG ; 

__attribute__((used)) static void permutate_in_line(int16_t *tab, int num_vect, int num_blocks,
                              int block_size,
                              const uint8_t line_len[2], int length_div,
                              enum TwinVQFrameType ftype)
{
    int i, j;

    for (i = 0; i < line_len[0]; i++) {
        int shift;

        if (num_blocks == 1                                    ||
            (ftype == TWINVQ_FT_LONG && num_vect % num_blocks) ||
            (ftype != TWINVQ_FT_LONG && num_vect & 1)          ||
            i == line_len[1]) {
            shift = 0;
        } else if (ftype == TWINVQ_FT_LONG) {
            shift = i;
        } else
            shift = i * i;

        for (j = 0; j < num_vect && (j + num_vect * i < block_size * num_blocks); j++)
            tab[i * num_vect + j] = i * num_vect + (j + shift) % num_vect;
    }
}