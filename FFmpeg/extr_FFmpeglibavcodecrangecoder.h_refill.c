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
struct TYPE_3__ {int range; int low; int /*<<< orphan*/  overread; scalar_t__* bytestream; scalar_t__* bytestream_end; } ;
typedef  TYPE_1__ RangeCoder ;

/* Variables and functions */

__attribute__((used)) static inline void refill(RangeCoder *c)
{
    if (c->range < 0x100) {
        c->range <<= 8;
        c->low   <<= 8;
        if (c->bytestream < c->bytestream_end) {
            c->low += c->bytestream[0];
            c->bytestream++;
        } else
            c->overread ++;
    }
}