#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * context; int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {size_t peerCount; struct TYPE_8__* peers; TYPE_1__ compressor; int /*<<< orphan*/  socket; } ;
typedef  TYPE_2__ ENetPeer ;
typedef  TYPE_2__ ENetHost ;

/* Variables and functions */
 int /*<<< orphan*/  enet_free (TYPE_2__*) ; 
 int /*<<< orphan*/  enet_peer_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  enet_socket_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
enet_host_destroy (ENetHost * host)
{
    ENetPeer * currentPeer;

    enet_socket_destroy (host -> socket);

    for (currentPeer = host -> peers;
         currentPeer < & host -> peers [host -> peerCount];
         ++ currentPeer)
    {
       enet_peer_reset (currentPeer);
    }

    if (host -> compressor.context != NULL && host -> compressor.destroy)
      (* host -> compressor.destroy) (host -> compressor.context);

    enet_free (host -> peers);
    enet_free (host);
}