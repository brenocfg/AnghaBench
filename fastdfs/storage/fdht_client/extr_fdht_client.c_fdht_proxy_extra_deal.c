#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int server_count; int group_count; int /*<<< orphan*/ * servers; TYPE_1__* groups; int /*<<< orphan*/  proxy_server; int /*<<< orphan*/  use_proxy; } ;
struct TYPE_4__ {int count; int /*<<< orphan*/ ** servers; } ;
typedef  TYPE_1__ ServerArray ;
typedef  TYPE_2__ GroupArray ;
typedef  int /*<<< orphan*/  FDHTServerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fdht_proxy_extra_deal(GroupArray *pGroupArray, bool *bKeepAlive)
{
	int group_id;
	ServerArray *pServerArray;
	FDHTServerInfo **ppServer;
	FDHTServerInfo **ppServerEnd;

	if (!pGroupArray->use_proxy)
	{
		return;
	}

	*bKeepAlive = true;
	pGroupArray->server_count = 1;
	memcpy(pGroupArray->servers, &pGroupArray->proxy_server, \
			sizeof(FDHTServerInfo));

	pServerArray = pGroupArray->groups;
	for (group_id=0; group_id<pGroupArray->group_count; group_id++)
	{
		ppServerEnd = pServerArray->servers + pServerArray->count;
		for (ppServer=pServerArray->servers; \
				ppServer<ppServerEnd; ppServer++)
		{
			*ppServer = pGroupArray->servers;
		}

		pServerArray++;
	}
}