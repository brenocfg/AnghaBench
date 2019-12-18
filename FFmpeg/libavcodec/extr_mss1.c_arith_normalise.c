#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  gb; } ;
struct TYPE_5__ {int high; int low; int value; TYPE_1__ gbc; int /*<<< orphan*/  overread; } ;
typedef  TYPE_2__ ArithCoder ;

/* Variables and functions */
 int get_bits1 (int /*<<< orphan*/ ) ; 
 int get_bits_left (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arith_normalise(ArithCoder *c)
{
    for (;;) {
        if (c->high >= 0x8000) {
            if (c->low < 0x8000) {
                if (c->low >= 0x4000 && c->high < 0xC000) {
                    c->value -= 0x4000;
                    c->low   -= 0x4000;
                    c->high  -= 0x4000;
                } else {
                    return;
                }
            } else {
                c->value -= 0x8000;
                c->low   -= 0x8000;
                c->high  -= 0x8000;
            }
        }
        c->value <<= 1;
        c->low   <<= 1;
        c->high  <<= 1;
        c->high   |= 1;
        if (get_bits_left(c->gbc.gb) < 1)
            c->overread++;
        c->value  |= get_bits1(c->gbc.gb);
    }
}