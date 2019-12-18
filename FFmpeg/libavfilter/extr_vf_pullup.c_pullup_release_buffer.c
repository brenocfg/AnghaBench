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
struct TYPE_3__ {int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ PullupBuffer ;

/* Variables and functions */

__attribute__((used)) static void pullup_release_buffer(PullupBuffer *b, int parity)
{
    if (!b)
        return;

    if ((parity + 1) & 1)
        b->lock[0]--;
    if ((parity + 1) & 2)
        b->lock[1]--;
}