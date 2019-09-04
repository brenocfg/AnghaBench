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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void transpose_perm(int16_t *out, int16_t *in, int num_vect,
                           const uint8_t line_len[2], int length_div)
{
    int i, j;
    int cont = 0;

    for (i = 0; i < num_vect; i++)
        for (j = 0; j < line_len[i >= length_div]; j++)
            out[cont++] = in[j * num_vect + i];
}