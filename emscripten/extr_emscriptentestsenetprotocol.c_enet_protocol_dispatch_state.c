#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dispatchQueue; } ;
struct TYPE_5__ {int needsDispatch; int /*<<< orphan*/  dispatchList; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  ENetPeerState ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetHost ;

/* Variables and functions */
 int /*<<< orphan*/  enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
enet_protocol_dispatch_state (ENetHost * host, ENetPeer * peer, ENetPeerState state)
{
    peer -> state = state;

    if (! peer -> needsDispatch)
    {
       enet_list_insert (enet_list_end (& host -> dispatchQueue), & peer -> dispatchList);

       peer -> needsDispatch = 1;
    }    
}