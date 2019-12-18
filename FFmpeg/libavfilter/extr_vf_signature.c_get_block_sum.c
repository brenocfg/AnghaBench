#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {int x; int y; } ;
struct TYPE_7__ {TYPE_2__ to; TYPE_1__ up; } ;
typedef  int /*<<< orphan*/  StreamContext ;
typedef  TYPE_3__ Block ;

/* Variables and functions */

__attribute__((used)) static uint64_t get_block_sum(StreamContext *sc, uint64_t intpic[32][32], const Block *b)
{
    uint64_t sum = 0;

    int x0, y0, x1, y1;

    x0 = b->up.x;
    y0 = b->up.y;
    x1 = b->to.x;
    y1 = b->to.y;

    if (x0-1 >= 0 && y0-1 >= 0) {
        sum = intpic[y1][x1] + intpic[y0-1][x0-1] - intpic[y1][x0-1] - intpic[y0-1][x1];
    } else if (x0-1 >= 0) {
        sum = intpic[y1][x1] - intpic[y1][x0-1];
    } else if (y0-1 >= 0) {
        sum = intpic[y1][x1] - intpic[y0-1][x1];
    } else {
        sum = intpic[y1][x1];
    }
    return sum;
}