#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  port; int /*<<< orphan*/ * ip; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {char* hostName; char* mapName; int ping; char* game; scalar_t__ netType; scalar_t__ gameType; scalar_t__ minPing; scalar_t__ maxPing; scalar_t__ maxClients; scalar_t__ clients; TYPE_1__ adr; } ;
typedef  TYPE_2__ serverInfo_t ;
struct TYPE_8__ {int /*<<< orphan*/  port; int /*<<< orphan*/ * ip; } ;
typedef  TYPE_3__ serverAddress_t ;

/* Variables and functions */
 int /*<<< orphan*/  NA_IP ; 

void CL_InitServerInfo( serverInfo_t *server, serverAddress_t *address ) {
	server->adr.type  = NA_IP;
	server->adr.ip[0] = address->ip[0];
	server->adr.ip[1] = address->ip[1];
	server->adr.ip[2] = address->ip[2];
	server->adr.ip[3] = address->ip[3];
	server->adr.port  = address->port;
	server->clients = 0;
	server->hostName[0] = '\0';
	server->mapName[0] = '\0';
	server->maxClients = 0;
	server->maxPing = 0;
	server->minPing = 0;
	server->ping = -1;
	server->game[0] = '\0';
	server->gameType = 0;
	server->netType = 0;
}