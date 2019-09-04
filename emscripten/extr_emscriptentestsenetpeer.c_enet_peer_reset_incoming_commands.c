#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ENetList ;

/* Variables and functions */
 int /*<<< orphan*/  enet_list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_peer_remove_incoming_commands (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enet_peer_reset_incoming_commands (ENetList * queue)
{
    enet_peer_remove_incoming_commands(queue, enet_list_begin (queue), enet_list_end(queue));
}