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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decode_colskip(uint8_t* plane, int width, int height, int stride,
                           GetBitContext *gb)
{
    int x, y;

    for (x = 0; x < width; x++) {
        if (!get_bits1(gb)) //colskip
            for (y = 0; y < height; y++)
                plane[y*stride] = 0;
        else
            for (y = 0; y < height; y++)
                plane[y*stride] = get_bits1(gb);
        plane ++;
    }
}