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
struct TYPE_4__ {struct TYPE_4__* fragments; TYPE_2__* packet; int /*<<< orphan*/  incomingCommandList; } ;
typedef  scalar_t__ ENetListIterator ;
typedef  int /*<<< orphan*/  ENetList ;
typedef  TYPE_1__ ENetIncomingCommand ;

/* Variables and functions */
 int /*<<< orphan*/  enet_free (TYPE_1__*) ; 
 scalar_t__ enet_list_next (scalar_t__) ; 
 int /*<<< orphan*/  enet_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_packet_destroy (TYPE_2__*) ; 

__attribute__((used)) static void
enet_peer_remove_incoming_commands (ENetList * queue, ENetListIterator startCommand, ENetListIterator endCommand)
{
    ENetListIterator currentCommand;    
    
    for (currentCommand = startCommand; currentCommand != endCommand; )
    {
       ENetIncomingCommand * incomingCommand = (ENetIncomingCommand *) currentCommand;

       currentCommand = enet_list_next (currentCommand);

       enet_list_remove (& incomingCommand -> incomingCommandList);
 
       if (incomingCommand -> packet != NULL)
       {
          -- incomingCommand -> packet -> referenceCount;

          if (incomingCommand -> packet -> referenceCount == 0)
            enet_packet_destroy (incomingCommand -> packet);
       }

       if (incomingCommand -> fragments != NULL)
         enet_free (incomingCommand -> fragments);

       enet_free (incomingCommand);
    }
}