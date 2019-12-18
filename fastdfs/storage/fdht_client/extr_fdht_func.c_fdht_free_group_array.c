#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int group_count; int server_count; TYPE_1__* groups; TYPE_1__* servers; } ;
struct TYPE_6__ {int sock; struct TYPE_6__* servers; } ;
typedef  TYPE_1__ ServerArray ;
typedef  TYPE_2__ GroupArray ;
typedef  TYPE_1__ FDHTServerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void fdht_free_group_array(GroupArray *pGroupArray)
{
	ServerArray *pServerArray;
	ServerArray *pArrayEnd;
	FDHTServerInfo *pServerInfo;
	FDHTServerInfo *pServerEnd;

	if (pGroupArray->servers != NULL)
	{
		pArrayEnd = pGroupArray->groups + pGroupArray->group_count;
		for (pServerArray=pGroupArray->groups; pServerArray<pArrayEnd;
			 pServerArray++)
		{
			if (pServerArray->servers == NULL)
			{
				continue;
			}

			free(pServerArray->servers);
			pServerArray->servers = NULL;
		}

		pServerEnd = pGroupArray->servers + pGroupArray->server_count;
		for (pServerInfo=pGroupArray->servers; \
				pServerInfo<pServerEnd; pServerInfo++)
		{
			if (pServerInfo->sock >= 0)
			{
				close(pServerInfo->sock);
				pServerInfo->sock = -1;
			}
		}

		free(pGroupArray->servers);
		pGroupArray->servers = NULL;
	}

	if (pGroupArray->groups != NULL)
	{
		free(pGroupArray->groups);
		pGroupArray->groups = NULL;
	}
}