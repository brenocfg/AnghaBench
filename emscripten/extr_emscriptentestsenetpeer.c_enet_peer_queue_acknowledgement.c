#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int enet_uint16 ;
struct TYPE_10__ {size_t channelID; int reliableSequenceNumber; } ;
struct TYPE_11__ {TYPE_1__ header; } ;
struct TYPE_14__ {int sentTime; TYPE_2__ command; } ;
struct TYPE_13__ {int incomingReliableSequenceNumber; } ;
struct TYPE_12__ {size_t channelCount; int outgoingDataTotal; int /*<<< orphan*/  acknowledgements; TYPE_4__* channels; } ;
typedef  int /*<<< orphan*/  ENetProtocolAcknowledge ;
typedef  TYPE_2__ ENetProtocol ;
typedef  TYPE_3__ ENetPeer ;
typedef  TYPE_4__ ENetChannel ;
typedef  TYPE_5__ ENetAcknowledgement ;

/* Variables and functions */
 int ENET_PEER_FREE_RELIABLE_WINDOWS ; 
 scalar_t__ ENET_PEER_RELIABLE_WINDOWS ; 
 int ENET_PEER_RELIABLE_WINDOW_SIZE ; 
 int /*<<< orphan*/  enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ enet_malloc (int) ; 

ENetAcknowledgement *
enet_peer_queue_acknowledgement (ENetPeer * peer, const ENetProtocol * command, enet_uint16 sentTime)
{
    ENetAcknowledgement * acknowledgement;

    if (command -> header.channelID < peer -> channelCount)
    {
        ENetChannel * channel = & peer -> channels [command -> header.channelID];
        enet_uint16 reliableWindow = command -> header.reliableSequenceNumber / ENET_PEER_RELIABLE_WINDOW_SIZE,
                    currentWindow = channel -> incomingReliableSequenceNumber / ENET_PEER_RELIABLE_WINDOW_SIZE;

        if (command -> header.reliableSequenceNumber < channel -> incomingReliableSequenceNumber)
           reliableWindow += ENET_PEER_RELIABLE_WINDOWS;

        if (reliableWindow >= currentWindow + ENET_PEER_FREE_RELIABLE_WINDOWS - 1 && reliableWindow <= currentWindow + ENET_PEER_FREE_RELIABLE_WINDOWS)
          return NULL;
    }

    acknowledgement = (ENetAcknowledgement *) enet_malloc (sizeof (ENetAcknowledgement));
    if (acknowledgement == NULL)
      return NULL;

    peer -> outgoingDataTotal += sizeof (ENetProtocolAcknowledge);

    acknowledgement -> sentTime = sentTime;
    acknowledgement -> command = * command;
    
    enet_list_insert (enet_list_end (& peer -> acknowledgements), acknowledgement);
    
    return acknowledgement;
}