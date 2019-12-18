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
struct TYPE_3__ {int fill; int queue; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ Bits8 ;

/* Variables and functions */
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_bits2(Bits8 *bits, GetByteContext *gb)
{
    int res;

    if (bits->fill == 0) {
        bits->queue |= bytestream2_get_byte(gb);
        bits->fill   = 8;
    }
    res = bits->queue >> 6;
    bits->queue <<= 2;
    bits->fill   -= 2;

    return res;
}