#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  visible; int /*<<< orphan*/  hostName; int /*<<< orphan*/  adr; } ;
typedef  TYPE_1__ serverInfo_t ;
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_4__ {int numlocalservers; int nummplayerservers; int numglobalservers; int numfavoriteservers; TYPE_1__* favoriteServers; TYPE_1__* globalServers; TYPE_1__* mplayerServers; TYPE_1__* localServers; } ;

/* Variables and functions */
#define  AS_FAVORITES 131 
#define  AS_GLOBAL 130 
#define  AS_LOCAL 129 
#define  AS_MPLAYER 128 
 int MAX_GLOBAL_SERVERS ; 
 int MAX_OTHER_SERVERS ; 
 scalar_t__ NET_CompareAdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_StringToAdr (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_2__ cls ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static int LAN_AddServer(int source, const char *name, const char *address) {
	int max, *count, i;
	netadr_t adr;
	serverInfo_t *servers = NULL;
	max = MAX_OTHER_SERVERS;
	count = 0;

	switch (source) {
		case AS_LOCAL :
			count = &cls.numlocalservers;
			servers = &cls.localServers[0];
			break;
		case AS_MPLAYER :
			count = &cls.nummplayerservers;
			servers = &cls.mplayerServers[0];
			break;
		case AS_GLOBAL :
			max = MAX_GLOBAL_SERVERS;
			count = &cls.numglobalservers;
			servers = &cls.globalServers[0];
			break;
		case AS_FAVORITES :
			count = &cls.numfavoriteservers;
			servers = &cls.favoriteServers[0];
			break;
	}
	if (servers && *count < max) {
		NET_StringToAdr( address, &adr );
		for ( i = 0; i < *count; i++ ) {
			if (NET_CompareAdr(servers[i].adr, adr)) {
				break;
			}
		}
		if (i >= *count) {
			servers[*count].adr = adr;
			Q_strncpyz(servers[*count].hostName, name, sizeof(servers[*count].hostName));
			servers[*count].visible = qtrue;
			(*count)++;
			return 1;
		}
		return 0;
	}
	return -1;
}