#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int player_count; TYPE_1__* players; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ Player ;

/* Variables and functions */
 int /*<<< orphan*/  del_buffer (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_player (int) ; 
 TYPE_4__* g ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

void delete_player(int id) {
    Player *player = find_player(id);
    if (!player) {
        return;
    }
    int count = g->player_count;
    del_buffer(player->buffer);
    Player *other = g->players + (--count);
    memcpy(player, other, sizeof(Player));
    g->player_count = count;
}