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
struct TYPE_4__ {int /*<<< orphan*/  gB; } ;
struct TYPE_5__ {int high; int low; TYPE_1__ gbc; } ;
typedef  TYPE_2__ ArithCoder ;

/* Variables and functions */
 int bytestream2_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arith2_get_consumed_bytes(ArithCoder *c)
{
    int diff = (c->high >> 16) - (c->low >> 16);
    int bp   = bytestream2_tell(c->gbc.gB) - 3 << 3;
    int bits = 1;

    while (!(diff & 0x80)) {
        bits++;
        diff <<= 1;
    }

    return (bits + bp + 7 >> 3) + ((c->low >> 16) + 1 == c->high >> 16);
}