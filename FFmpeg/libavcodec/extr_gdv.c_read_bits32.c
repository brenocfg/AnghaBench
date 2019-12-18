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
struct TYPE_3__ {int queue; int fill; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ Bits32 ;

/* Variables and functions */
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_bits32(Bits32 *bits, GetByteContext *gb, int nbits)
{
    int res = bits->queue & ((1 << nbits) - 1);

    bits->queue >>= nbits;
    bits->fill   -= nbits;
    if (bits->fill <= 16) {
        bits->queue |= bytestream2_get_le16(gb) << bits->fill;
        bits->fill  += 16;
    }

    return res;
}