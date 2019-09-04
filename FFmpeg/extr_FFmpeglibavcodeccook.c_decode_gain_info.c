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
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_left (int /*<<< orphan*/ *) ; 
 int get_unary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_gain_info(GetBitContext *gb, int *gaininfo)
{
    int i, n;

    n = get_unary(gb, 0, get_bits_left(gb));     // amount of elements*2 to update

    i = 0;
    while (n--) {
        int index = get_bits(gb, 3);
        int gain = get_bits1(gb) ? get_bits(gb, 4) - 7 : -1;

        while (i <= index)
            gaininfo[i++] = gain;
    }
    while (i <= 8)
        gaininfo[i++] = 0;
}