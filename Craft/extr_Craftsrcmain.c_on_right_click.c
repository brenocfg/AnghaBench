#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t item_index; TYPE_1__* players; } ;
struct TYPE_5__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  ry; int /*<<< orphan*/  rx; } ;
struct TYPE_4__ {TYPE_2__ state; } ;
typedef  TYPE_2__ State ;

/* Variables and functions */
 TYPE_3__* g ; 
 int hit_test (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 scalar_t__ is_obstacle (int) ; 
 int /*<<< orphan*/ * items ; 
 int /*<<< orphan*/  player_intersects_block (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  record_block (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_block (int,int,int,int /*<<< orphan*/ ) ; 

void on_right_click() {
    State *s = &g->players->state;
    int hx, hy, hz;
    int hw = hit_test(1, s->x, s->y, s->z, s->rx, s->ry, &hx, &hy, &hz);
    if (hy > 0 && hy < 256 && is_obstacle(hw)) {
        if (!player_intersects_block(2, s->x, s->y, s->z, hx, hy, hz)) {
            set_block(hx, hy, hz, items[g->item_index]);
            record_block(hx, hy, hz, items[g->item_index]);
        }
    }
}