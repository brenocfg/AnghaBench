#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int player_count; TYPE_1__* players; } ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ Player ;

/* Variables and functions */
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 TYPE_2__* g ; 

void delete_all_players() {
    for (int i = 0; i < g->player_count; i++) {
        Player *player = g->players + i;
        del_buffer(player->buffer);
    }
    g->player_count = 0;
}