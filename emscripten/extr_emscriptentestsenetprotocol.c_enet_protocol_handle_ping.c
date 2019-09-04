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
typedef  int /*<<< orphan*/  ENetProtocol ;
typedef  int /*<<< orphan*/  ENetPeer ;
typedef  int /*<<< orphan*/  ENetHost ;

/* Variables and functions */

__attribute__((used)) static int
enet_protocol_handle_ping (ENetHost * host, ENetPeer * peer, const ENetProtocol * command)
{
    return 0;
}