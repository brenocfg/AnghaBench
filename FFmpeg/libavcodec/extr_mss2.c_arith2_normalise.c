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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  gB; } ;
struct TYPE_5__ {int high; int low; int value; TYPE_1__ gbc; } ;
typedef  TYPE_2__ ArithCoder ;

/* Variables and functions */
 int bytestream2_get_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arith2_normalise(ArithCoder *c)
{
    while ((c->high >> 15) - (c->low >> 15) < 2) {
        if ((c->low ^ c->high) & 0x10000) {
            c->high  ^= 0x8000;
            c->value ^= 0x8000;
            c->low   ^= 0x8000;
        }
        c->high  = (uint16_t)c->high  << 8  | 0xFF;
        c->value = (uint16_t)c->value << 8  | bytestream2_get_byte(c->gbc.gB);
        c->low   = (uint16_t)c->low   << 8;
    }
}