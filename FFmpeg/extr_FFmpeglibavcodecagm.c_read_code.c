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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_code(GetBitContext *gb, int *oskip, int *level, int *map, int mode)
{
    int len = 0, skip = 0, max;

    if (get_bits_left(gb) < 2)
        return AVERROR_INVALIDDATA;

    if (show_bits(gb, 2)) {
        switch (show_bits(gb, 4)) {
        case 1:
        case 9:
            len = 1;
            skip = 3;
            break;
        case 2:
            len = 3;
            skip = 4;
            break;
        case 3:
            len = 7;
            skip = 4;
            break;
        case 5:
        case 13:
            len = 2;
            skip = 3;
            break;
        case 6:
            len = 4;
            skip = 4;
            break;
        case 7:
            len = 8;
            skip = 4;
            break;
        case 10:
            len = 5;
            skip = 4;
            break;
        case 11:
            len = 9;
            skip = 4;
            break;
        case 14:
            len = 6;
            skip = 4;
            break;
        case 15:
            len = ((show_bits(gb, 5) & 0x10) | 0xA0) >> 4;
            skip = 5;
            break;
        default:
            return AVERROR_INVALIDDATA;
        }

        skip_bits(gb, skip);
        *level = get_bits(gb, len);
        *map = 1;
        *oskip = 0;
        max = 1 << (len - 1);
        if (*level < max)
            *level = -(max + *level);
    } else if (show_bits(gb, 3) & 4) {
        skip_bits(gb, 3);
        if (mode == 1) {
            if (show_bits(gb, 4)) {
                if (show_bits(gb, 4) == 1) {
                    skip_bits(gb, 4);
                    *oskip = get_bits(gb, 16);
                } else {
                    *oskip = get_bits(gb, 4);
                }
            } else {
                skip_bits(gb, 4);
                *oskip = get_bits(gb, 10);
            }
        } else if (mode == 0) {
            *oskip = get_bits(gb, 10);
        }
        *level = 0;
    } else {
        skip_bits(gb, 3);
        if (mode == 0)
            *oskip = get_bits(gb, 4);
        else if (mode == 1)
            *oskip = 0;
        *level = 0;
    }

    return 0;
}