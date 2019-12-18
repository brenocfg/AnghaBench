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
struct TYPE_7__ {scalar_t__ sock; } ;
struct TYPE_6__ {int count; TYPE_2__** servers; } ;
typedef  TYPE_1__ ServerArray ;
typedef  TYPE_2__ FDHTServerInfo ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ fdht_connect_server_nb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_fdht_connect_timeout ; 
 int /*<<< orphan*/  tcpsetnodelay (scalar_t__,int) ; 

__attribute__((used)) static FDHTServerInfo *get_connection(ServerArray *pServerArray, \
		const bool bKeepAlive, const int hash_code, int *err_no)
{
	FDHTServerInfo **ppServer;
	FDHTServerInfo **ppEnd;
	int server_index;
	int new_hash_code;

	new_hash_code = (hash_code << 16) | (hash_code >> 16);
	if (new_hash_code < 0)
	{
		new_hash_code &= 0x7FFFFFFF;
	}
	server_index = new_hash_code % pServerArray->count;
	ppEnd = pServerArray->servers + pServerArray->count;
	for (ppServer = pServerArray->servers + server_index; \
		ppServer<ppEnd; ppServer++)
	{
		if ((*ppServer)->sock > 0)  //already connected
		{
			return *ppServer;
		}

		if (fdht_connect_server_nb(*ppServer, \
			g_fdht_connect_timeout) == 0)
		{
			if (bKeepAlive)
			{
				tcpsetnodelay((*ppServer)->sock, 3600);
			}
			return *ppServer;
		}
	}

	ppEnd = pServerArray->servers + server_index;
	for (ppServer = pServerArray->servers; ppServer<ppEnd; ppServer++)
	{
		if ((*ppServer)->sock > 0)  //already connected
		{
			return *ppServer;
		}

		if (fdht_connect_server_nb(*ppServer, \
			g_fdht_connect_timeout) == 0)
		{
			if (bKeepAlive)
			{
				tcpsetnodelay((*ppServer)->sock, 3600);
			}
			return *ppServer;
		}
	}

	*err_no = ENOENT;
	return NULL;
}