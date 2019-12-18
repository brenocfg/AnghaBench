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
struct TYPE_3__ {int code; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode3(GetByteContext *gb, RangeCoder *rc, uint32_t a, uint32_t b)
{
    uint32_t code = a * (rc->code >> 12) + (rc->code & 0xFFF) - b;

    while (code < 0x800000 && bytestream2_get_bytes_left(gb) > 0)
        code = bytestream2_get_byteu(gb) | (code << 8);
    rc->code = code;

    return 0;
}