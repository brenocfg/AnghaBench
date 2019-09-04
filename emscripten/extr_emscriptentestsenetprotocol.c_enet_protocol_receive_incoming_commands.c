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
struct TYPE_7__ {int dataLength; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int receivedDataLength; int totalReceivedData; int /*<<< orphan*/  totalReceivedPackets; int /*<<< orphan*/ * packetData; int /*<<< orphan*/  receivedData; int /*<<< orphan*/  receivedAddress; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ ENetHost ;
typedef  int /*<<< orphan*/  ENetEvent ;
typedef  TYPE_2__ ENetBuffer ;

/* Variables and functions */
 int enet_protocol_handle_incoming_commands (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int enet_socket_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static int
enet_protocol_receive_incoming_commands (ENetHost * host, ENetEvent * event)
{
    for (;;)
    {
       int receivedLength;
       ENetBuffer buffer;

       buffer.data = host -> packetData [0];
       buffer.dataLength = sizeof (host -> packetData [0]);

       receivedLength = enet_socket_receive (host -> socket,
                                             & host -> receivedAddress,
                                             & buffer,
                                             1);

       if (receivedLength < 0)
         return -1;

       if (receivedLength == 0)
         return 0;

       host -> receivedData = host -> packetData [0];
       host -> receivedDataLength = receivedLength;
      
       host -> totalReceivedData += receivedLength;
       host -> totalReceivedPackets ++;
 
       switch (enet_protocol_handle_incoming_commands (host, event))
       {
       case 1:
          return 1;
       
       case -1:
          return -1;

       default:
          break;
       }
    }

    return -1;
}