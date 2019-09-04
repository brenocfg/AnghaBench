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
typedef  int uint32_t ;
struct TYPE_3__ {int code; int range; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int TOP ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode(GetByteContext *gb, RangeCoder *rc, uint32_t cumFreq, uint32_t freq, uint32_t total_freq)
{
    rc->code -= cumFreq * rc->range;
    rc->range *= freq;

    while (rc->range < TOP && bytestream2_get_bytes_left(gb) > 0) {
        uint32_t byte = bytestream2_get_byteu(gb);
        rc->code = (rc->code << 8) | byte;
        rc->range <<= 8;
    }

    return 0;
}