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
struct TYPE_7__ {int /*<<< orphan*/  incomingUnreliableCommands; int /*<<< orphan*/  incomingReliableCommands; } ;
struct TYPE_6__ {size_t channelCount; TYPE_2__* channels; int /*<<< orphan*/  dispatchedCommands; int /*<<< orphan*/  outgoingUnreliableCommands; int /*<<< orphan*/  outgoingReliableCommands; int /*<<< orphan*/  sentUnreliableCommands; int /*<<< orphan*/  sentReliableCommands; int /*<<< orphan*/  acknowledgements; scalar_t__ needsDispatch; int /*<<< orphan*/  dispatchList; } ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetChannel ;

/* Variables and functions */
 int /*<<< orphan*/  enet_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * enet_list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_empty (int /*<<< orphan*/ *) ; 
 TYPE_2__* enet_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_peer_reset_incoming_commands (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_peer_reset_outgoing_commands (int /*<<< orphan*/ *) ; 

void
enet_peer_reset_queues (ENetPeer * peer)
{
    ENetChannel * channel;

    if (peer -> needsDispatch)
    {
       enet_list_remove (& peer -> dispatchList);

       peer -> needsDispatch = 0;
    }

    while (! enet_list_empty (& peer -> acknowledgements))
      enet_free (enet_list_remove (enet_list_begin (& peer -> acknowledgements)));

    enet_peer_reset_outgoing_commands (& peer -> sentReliableCommands);
    enet_peer_reset_outgoing_commands (& peer -> sentUnreliableCommands);
    enet_peer_reset_outgoing_commands (& peer -> outgoingReliableCommands);
    enet_peer_reset_outgoing_commands (& peer -> outgoingUnreliableCommands);
    enet_peer_reset_incoming_commands (& peer -> dispatchedCommands);

    if (peer -> channels != NULL && peer -> channelCount > 0)
    {
        for (channel = peer -> channels;
             channel < & peer -> channels [peer -> channelCount];
             ++ channel)
        {
            enet_peer_reset_incoming_commands (& channel -> incomingReliableCommands);
            enet_peer_reset_incoming_commands (& channel -> incomingUnreliableCommands);
        }

        enet_free (peer -> channels);
    }

    peer -> channels = NULL;
    peer -> channelCount = 0;
}