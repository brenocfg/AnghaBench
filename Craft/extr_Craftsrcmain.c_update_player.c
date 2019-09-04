#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; float z; float rx; float ry; int /*<<< orphan*/  t; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; TYPE_1__ state; TYPE_1__ state2; TYPE_1__ state1; } ;
typedef  TYPE_1__ State ;
typedef  TYPE_2__ Player ;

/* Variables and functions */
 int PI ; 
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_player_buffer (float,float,float,float,float) ; 
 int /*<<< orphan*/  glfwGetTime () ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

void update_player(Player *player,
    float x, float y, float z, float rx, float ry, int interpolate)
{
    if (interpolate) {
        State *s1 = &player->state1;
        State *s2 = &player->state2;
        memcpy(s1, s2, sizeof(State));
        s2->x = x; s2->y = y; s2->z = z; s2->rx = rx; s2->ry = ry;
        s2->t = glfwGetTime();
        if (s2->rx - s1->rx > PI) {
            s1->rx += 2 * PI;
        }
        if (s1->rx - s2->rx > PI) {
            s1->rx -= 2 * PI;
        }
    }
    else {
        State *s = &player->state;
        s->x = x; s->y = y; s->z = z; s->rx = rx; s->ry = ry;
        del_buffer(player->buffer);
        player->buffer = gen_player_buffer(s->x, s->y, s->z, s->rx, s->ry);
    }
}