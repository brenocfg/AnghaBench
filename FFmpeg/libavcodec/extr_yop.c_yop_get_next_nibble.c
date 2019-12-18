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
typedef  int uint8_t ;
struct TYPE_3__ {int* low_nibble; int /*<<< orphan*/  srcptr; } ;
typedef  TYPE_1__ YopDecContext ;

/* Variables and functions */

__attribute__((used)) static uint8_t yop_get_next_nibble(YopDecContext *s)
{
    int ret;

    if (s->low_nibble) {
        ret           = *s->low_nibble & 0xf;
        s->low_nibble = NULL;
    }else {
        s->low_nibble = s->srcptr++;
        ret           = *s->low_nibble >> 4;
    }
    return ret;
}