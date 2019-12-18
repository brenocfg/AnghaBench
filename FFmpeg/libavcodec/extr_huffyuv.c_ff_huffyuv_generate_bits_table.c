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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int ff_huffyuv_generate_bits_table(uint32_t *dst, const uint8_t *len_table, int n)
{
    int len, index;
    uint32_t bits = 0;

    for (len = 32; len > 0; len--) {
        for (index = 0; index < n; index++) {
            if (len_table[index] == len)
                dst[index] = bits++;
        }
        if (bits & 1) {
            av_log(NULL, AV_LOG_ERROR, "Error generating huffman table\n");
            return -1;
        }
        bits >>= 1;
    }
    return 0;
}