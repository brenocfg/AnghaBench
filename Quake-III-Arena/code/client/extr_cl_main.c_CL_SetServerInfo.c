#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ping; void* punkbuster; void* maxPing; void* minPing; void* netType; void* gameType; int /*<<< orphan*/  game; void* maxClients; int /*<<< orphan*/  mapName; int /*<<< orphan*/  hostName; void* clients; } ;
typedef  TYPE_1__ serverInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  Info_ValueForKey (char const*,char*) ; 
 int /*<<< orphan*/  MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* atoi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CL_SetServerInfo(serverInfo_t *server, const char *info, int ping) {
	if (server) {
		if (info) {
			server->clients = atoi(Info_ValueForKey(info, "clients"));
			Q_strncpyz(server->hostName,Info_ValueForKey(info, "hostname"), MAX_NAME_LENGTH);
			Q_strncpyz(server->mapName, Info_ValueForKey(info, "mapname"), MAX_NAME_LENGTH);
			server->maxClients = atoi(Info_ValueForKey(info, "sv_maxclients"));
			Q_strncpyz(server->game,Info_ValueForKey(info, "game"), MAX_NAME_LENGTH);
			server->gameType = atoi(Info_ValueForKey(info, "gametype"));
			server->netType = atoi(Info_ValueForKey(info, "nettype"));
			server->minPing = atoi(Info_ValueForKey(info, "minping"));
			server->maxPing = atoi(Info_ValueForKey(info, "maxping"));
			server->punkbuster = atoi(Info_ValueForKey(info, "punkbuster"));
		}
		server->ping = ping;
	}
}