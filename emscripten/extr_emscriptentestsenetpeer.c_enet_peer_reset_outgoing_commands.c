#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ referenceCount; } ;
struct TYPE_4__ {TYPE_2__* packet; } ;
typedef  TYPE_1__ ENetOutgoingCommand ;
typedef  int /*<<< orphan*/  ENetList ;

/* Variables and functions */
 int /*<<< orphan*/  enet_free (TYPE_1__*) ; 
 int /*<<< orphan*/  enet_list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_packet_destroy (TYPE_2__*) ; 

__attribute__((used)) static void
enet_peer_reset_outgoing_commands (ENetList * queue)
{
    ENetOutgoingCommand * outgoingCommand;

    while (! enet_list_empty (queue))
    {
       outgoingCommand = (ENetOutgoingCommand *) enet_list_remove (enet_list_begin (queue));

       if (outgoingCommand -> packet != NULL)
       {
          -- outgoingCommand -> packet -> referenceCount;

          if (outgoingCommand -> packet -> referenceCount == 0)
            enet_packet_destroy (outgoingCommand -> packet);
       }

       enet_free (outgoingCommand);
    }
}