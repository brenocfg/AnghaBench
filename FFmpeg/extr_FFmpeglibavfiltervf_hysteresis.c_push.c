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
typedef  int uint16_t ;
struct TYPE_3__ {int* map; int* xy; size_t index; } ;
typedef  TYPE_1__ HysteresisContext ;

/* Variables and functions */

__attribute__((used)) static void push(HysteresisContext *s, int x, int y, int w)
{
    s->map[x + y * w] = 0xff;
    s->xy[++s->index] = (uint16_t)(x) << 16 | (uint16_t)y;
}