#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  serviceTime; } ;
struct TYPE_9__ {scalar_t__ roundTripTimeout; scalar_t__ roundTripTimeoutLimit; scalar_t__ sentTime; int /*<<< orphan*/  outgoingCommandList; scalar_t__ fragmentLength; int /*<<< orphan*/ * packet; } ;
struct TYPE_8__ {scalar_t__ nextTimeout; int /*<<< orphan*/  sentReliableCommands; int /*<<< orphan*/  packetsLost; int /*<<< orphan*/  reliableDataInTransit; scalar_t__ earliestTimeout; int /*<<< orphan*/  outgoingReliableCommands; } ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetOutgoingCommand ;
typedef  scalar_t__ ENetListIterator ;
typedef  TYPE_3__ ENetHost ;
typedef  int /*<<< orphan*/  ENetEvent ;

/* Variables and functions */
 scalar_t__ ENET_PEER_TIMEOUT_MAXIMUM ; 
 scalar_t__ ENET_PEER_TIMEOUT_MINIMUM ; 
 scalar_t__ ENET_TIME_DIFFERENCE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ENET_TIME_LESS (scalar_t__,scalar_t__) ; 
 scalar_t__ enet_list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ enet_list_next (scalar_t__) ; 
 int /*<<< orphan*/  enet_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_protocol_notify_disconnect (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
enet_protocol_check_timeouts (ENetHost * host, ENetPeer * peer, ENetEvent * event)
{
    ENetOutgoingCommand * outgoingCommand;
    ENetListIterator currentCommand, insertPosition;

    currentCommand = enet_list_begin (& peer -> sentReliableCommands);
    insertPosition = enet_list_begin (& peer -> outgoingReliableCommands);

    while (currentCommand != enet_list_end (& peer -> sentReliableCommands))
    {
       outgoingCommand = (ENetOutgoingCommand *) currentCommand;

       currentCommand = enet_list_next (currentCommand);

       if (ENET_TIME_DIFFERENCE (host -> serviceTime, outgoingCommand -> sentTime) < outgoingCommand -> roundTripTimeout)
         continue;

       if (peer -> earliestTimeout == 0 ||
           ENET_TIME_LESS (outgoingCommand -> sentTime, peer -> earliestTimeout))
         peer -> earliestTimeout = outgoingCommand -> sentTime;

       if (peer -> earliestTimeout != 0 &&
             (ENET_TIME_DIFFERENCE (host -> serviceTime, peer -> earliestTimeout) >= ENET_PEER_TIMEOUT_MAXIMUM ||
               (outgoingCommand -> roundTripTimeout >= outgoingCommand -> roundTripTimeoutLimit &&
                 ENET_TIME_DIFFERENCE (host -> serviceTime, peer -> earliestTimeout) >= ENET_PEER_TIMEOUT_MINIMUM)))
       {
          enet_protocol_notify_disconnect (host, peer, event);

          return 1;
       }

       if (outgoingCommand -> packet != NULL)
         peer -> reliableDataInTransit -= outgoingCommand -> fragmentLength;
          
       ++ peer -> packetsLost;

       outgoingCommand -> roundTripTimeout *= 2;

       enet_list_insert (insertPosition, enet_list_remove (& outgoingCommand -> outgoingCommandList));

       if (currentCommand == enet_list_begin (& peer -> sentReliableCommands) &&
           ! enet_list_empty (& peer -> sentReliableCommands))
       {
          outgoingCommand = (ENetOutgoingCommand *) currentCommand;

          peer -> nextTimeout = outgoingCommand -> sentTime + outgoingCommand -> roundTripTimeout;
       }
    }
    
    return 0;
}