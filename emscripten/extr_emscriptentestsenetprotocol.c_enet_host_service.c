#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ enet_uint32 ;
struct TYPE_13__ {int /*<<< orphan*/ * packet; int /*<<< orphan*/ * peer; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {scalar_t__ serviceTime; scalar_t__ bandwidthThrottleEpoch; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ ENetHost ;
typedef  TYPE_2__ ENetEvent ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_EVENT_TYPE_NONE ; 
 scalar_t__ ENET_HOST_BANDWIDTH_THROTTLE_INTERVAL ; 
 scalar_t__ ENET_SOCKET_WAIT_RECEIVE ; 
 scalar_t__ ENET_TIME_DIFFERENCE (scalar_t__,scalar_t__) ; 
 scalar_t__ ENET_TIME_GREATER_EQUAL (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  enet_host_bandwidth_throttle (TYPE_1__*) ; 
 int enet_protocol_dispatch_incoming_commands (TYPE_1__*,TYPE_2__*) ; 
 int enet_protocol_receive_incoming_commands (TYPE_1__*,TYPE_2__*) ; 
 int enet_protocol_send_outgoing_commands (TYPE_1__*,TYPE_2__*,int) ; 
 scalar_t__ enet_socket_wait (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 void* enet_time_get () ; 
 int /*<<< orphan*/  perror (char*) ; 

int
enet_host_service (ENetHost * host, ENetEvent * event, enet_uint32 timeout)
{
    enet_uint32 waitCondition;

    if (event != NULL)
    {
        event -> type = ENET_EVENT_TYPE_NONE;
        event -> peer = NULL;
        event -> packet = NULL;

        switch (enet_protocol_dispatch_incoming_commands (host, event))
        {
        case 1:
            return 1;

        case -1:
            perror ("Error dispatching incoming packets");

            return -1;

        default:
            break;
        }
    }

    host -> serviceTime = enet_time_get ();
    
    timeout += host -> serviceTime;

    do
    {
       if (ENET_TIME_DIFFERENCE (host -> serviceTime, host -> bandwidthThrottleEpoch) >= ENET_HOST_BANDWIDTH_THROTTLE_INTERVAL)
         enet_host_bandwidth_throttle (host);

       switch (enet_protocol_send_outgoing_commands (host, event, 1))
       {
       case 1:
          return 1;

       case -1:
          perror ("Error sending outgoing packets");

          return -1;

       default:
          break;
       }

       switch (enet_protocol_receive_incoming_commands (host, event))
       {
       case 1:
          return 1;

       case -1:
          perror ("Error receiving incoming packets");

          return -1;

       default:
          break;
       }

       switch (enet_protocol_send_outgoing_commands (host, event, 1))
       {
       case 1:
          return 1;

       case -1:
          perror ("Error sending outgoing packets");

          return -1;

       default:
          break;
       }

       if (event != NULL)
       {
          switch (enet_protocol_dispatch_incoming_commands (host, event))
          {
          case 1:
             return 1;

          case -1:
             perror ("Error dispatching incoming packets");

             return -1;

          default:
             break;
          }
       }

       host -> serviceTime = enet_time_get ();

       if (ENET_TIME_GREATER_EQUAL (host -> serviceTime, timeout))
         return 0;

       waitCondition = ENET_SOCKET_WAIT_RECEIVE;

       if (enet_socket_wait (host -> socket, & waitCondition, ENET_TIME_DIFFERENCE (timeout, host -> serviceTime)) != 0)
         return -1;
       
       host -> serviceTime = enet_time_get ();
    } while (waitCondition == ENET_SOCKET_WAIT_RECEIVE);

    return 0; 
}