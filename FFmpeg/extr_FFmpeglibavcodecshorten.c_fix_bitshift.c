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
typedef  unsigned int int32_t ;
struct TYPE_3__ {int bitshift; int blocksize; } ;
typedef  TYPE_1__ ShortenContext ;

/* Variables and functions */

__attribute__((used)) static void fix_bitshift(ShortenContext *s, int32_t *buffer)
{
    int i;

    if (s->bitshift == 32) {
        for (i = 0; i < s->blocksize; i++)
            buffer[i] = 0;
    } else if (s->bitshift != 0) {
        for (i = 0; i < s->blocksize; i++)
            buffer[i] *= 1U << s->bitshift;
    }
}