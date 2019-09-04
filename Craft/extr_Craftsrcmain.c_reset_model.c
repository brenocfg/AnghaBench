#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double day_length; int time_changed; scalar_t__ message_index; int /*<<< orphan*/  messages; scalar_t__ typing; int /*<<< orphan*/  typing_buffer; scalar_t__ item_index; scalar_t__ flying; scalar_t__ observe2; scalar_t__ observe1; scalar_t__ player_count; int /*<<< orphan*/  players; scalar_t__ chunk_count; int /*<<< orphan*/  chunks; } ;
typedef  int /*<<< orphan*/  Player ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 double DAY_LENGTH ; 
 int MAX_CHUNKS ; 
 int MAX_MESSAGES ; 
 int MAX_PLAYERS ; 
 int MAX_TEXT_LENGTH ; 
 TYPE_1__* g ; 
 int /*<<< orphan*/  glfwSetTime (double) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void reset_model() {
    memset(g->chunks, 0, sizeof(Chunk) * MAX_CHUNKS);
    g->chunk_count = 0;
    memset(g->players, 0, sizeof(Player) * MAX_PLAYERS);
    g->player_count = 0;
    g->observe1 = 0;
    g->observe2 = 0;
    g->flying = 0;
    g->item_index = 0;
    memset(g->typing_buffer, 0, sizeof(char) * MAX_TEXT_LENGTH);
    g->typing = 0;
    memset(g->messages, 0, sizeof(char) * MAX_MESSAGES * MAX_TEXT_LENGTH);
    g->message_index = 0;
    g->day_length = DAY_LENGTH;
    glfwSetTime(g->day_length / 3.0);
    g->time_changed = 1;
}