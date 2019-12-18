#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sock; int /*<<< orphan*/  ip_addr; } ;
typedef  TYPE_1__ ConnectionInfo ;

/* Variables and functions */
 int conn_pool_connect_server (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_fdfs_connect_timeout ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int storage_server_count ; 
 TYPE_1__* storage_servers ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ConnectionInfo *getConnectedStorageServer(
		ConnectionInfo *pStorageServer, int *err_no)
{
	ConnectionInfo *pEnd;
	ConnectionInfo *pServer;

	pEnd = storage_servers + storage_server_count;
	for (pServer=storage_servers; pServer<pEnd; pServer++)
	{
		if (strcmp(pStorageServer->ip_addr, pServer->ip_addr) == 0)
		{
			if (pServer->sock < 0)
			{
				*err_no = conn_pool_connect_server(pServer, \
					g_fdfs_connect_timeout);
				if (*err_no != 0)
				{
					return NULL;
				}
			}
			else
			{
				*err_no = 0;
			}

			return pServer;
		}
	}

	pServer = pEnd;
	memcpy(pServer, pStorageServer, sizeof(ConnectionInfo));
	pServer->sock = -1;
	if ((*err_no=conn_pool_connect_server(pServer, \
		g_fdfs_connect_timeout)) != 0)
	{
		return NULL;
	}

	storage_server_count++;

	*err_no = 0;
	return pServer;
}