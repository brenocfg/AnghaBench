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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_len_table(uint8_t *dst, GetBitContext *gb, int n)
{
    int i, val, repeat;

    for (i = 0; i < n;) {
        repeat = get_bits(gb, 3);
        val    = get_bits(gb, 5);
        if (repeat == 0)
            repeat = get_bits(gb, 8);
        if (i + repeat > n || get_bits_left(gb) < 0) {
            av_log(NULL, AV_LOG_ERROR, "Error reading huffman table\n");
            return AVERROR_INVALIDDATA;
        }
        while (repeat--)
            dst[i++] = val;
    }
    return 0;
}