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
struct TYPE_6__ {int sock; } ;
struct TYPE_5__ {int server_count; int /*<<< orphan*/  use_proxy; TYPE_2__* servers; } ;
typedef  TYPE_1__ GroupArray ;
typedef  TYPE_2__ FDHTServerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fdht_quit (TYPE_2__*) ; 

void fdht_disconnect_all_servers(GroupArray *pGroupArray)
{
	FDHTServerInfo *pServerInfo;
	FDHTServerInfo *pServerEnd;

	if (pGroupArray->servers != NULL)
	{
		pServerEnd = pGroupArray->servers + pGroupArray->server_count;
		for (pServerInfo=pGroupArray->servers; \
				pServerInfo<pServerEnd; pServerInfo++)
		{
			if (pServerInfo->sock >= 0)
			{
				if (!pGroupArray->use_proxy)
				{
					fdht_quit(pServerInfo);
				}
				close(pServerInfo->sock);
				pServerInfo->sock = -1;
			}
		}
	}
}