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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int channels; int* channel_order_tab; int /*<<< orphan*/ ** history; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */

__attribute__((used)) static void shift_history(DCAEncContext *c, const int32_t *input)
{
    int k, ch;

    for (k = 0; k < 512; k++)
        for (ch = 0; ch < c->channels; ch++) {
            const int chi = c->channel_order_tab[ch];

            c->history[ch][k] = input[k * c->channels + chi];
        }
}