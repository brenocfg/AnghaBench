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
struct TYPE_6__ {int /*<<< orphan*/  sock; } ;
struct TYPE_5__ {int server_count; scalar_t__ use_proxy; TYPE_2__* servers; } ;
typedef  TYPE_1__ GroupArray ;
typedef  TYPE_2__ FDHTServerInfo ;

/* Variables and functions */
 int ENOENT ; 
 int fdht_connect_server_nb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_fdht_connect_timeout ; 
 int /*<<< orphan*/  tcpsetnodelay (int /*<<< orphan*/ ,int) ; 

int fdht_connect_all_servers(GroupArray *pGroupArray, const bool bKeepAlive, \
			int *success_count, int *fail_count)
{
	FDHTServerInfo *pServerInfo;
	FDHTServerInfo *pServerEnd;
	int conn_result;
	int result;

	*success_count = 0;
	*fail_count = 0;
	if (pGroupArray->servers == NULL)
	{
		return ENOENT;
	}

	result = 0;

	pServerEnd = pGroupArray->servers + pGroupArray->server_count;
	for (pServerInfo=pGroupArray->servers; \
			pServerInfo<pServerEnd; pServerInfo++)
	{
		if ((conn_result=fdht_connect_server_nb(pServerInfo, \
				g_fdht_connect_timeout)) != 0)
		{
			result = conn_result;
			(*fail_count)++;
		}
		else //connect success
		{
			(*success_count)++;
			if (bKeepAlive || pGroupArray->use_proxy)
			{
				tcpsetnodelay(pServerInfo->sock, 3600);
			}
		}
	}

	if (result != 0)
	{
		return result;
	}
	else
	{
		return  *success_count > 0 ? 0: ENOENT;
	}
}