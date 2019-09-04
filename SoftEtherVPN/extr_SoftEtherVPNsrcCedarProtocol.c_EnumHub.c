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
typedef  int /*<<< orphan*/  tmp ;
typedef  int UINT ;
struct TYPE_8__ {int /*<<< orphan*/ * FirstSock; } ;
struct TYPE_7__ {TYPE_3__* Connection; } ;
struct TYPE_6__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_2__ SESSION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpClientRecv (int /*<<< orphan*/ *) ; 
 int HttpClientSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddClientVersion (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int PackGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetStrEx (int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,int) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *EnumHub(SESSION *s)
{
	SOCK *sock;
	TOKEN_LIST *ret;
	PACK *p;
	UINT num;
	UINT i;
	// Validate arguments
	if (s == NULL || s->Connection == NULL)
	{
		return NULL;
	}

	sock = s->Connection->FirstSock;
	if (sock == NULL)
	{
		return NULL;
	}

	// Set the Timeout
	SetTimeout(sock, 10000);

	p = NewPack();
	PackAddStr(p, "method", "enum_hub");

	PackAddClientVersion(p, s->Connection);

	if (HttpClientSend(sock, p) == false)
	{
		FreePack(p);
		return NULL;
	}
	FreePack(p);

	p = HttpClientRecv(sock);
	if (p == NULL)
	{
		return NULL;
	}

	num = PackGetInt(p, "NumHub");
	ret = ZeroMalloc(sizeof(TOKEN_LIST));
	ret->NumTokens = num;
	ret->Token = ZeroMalloc(sizeof(char *) * num);
	for (i = 0;i < num;i++)
	{
		char tmp[MAX_SIZE];
		if (PackGetStrEx(p, "HubName", tmp, sizeof(tmp), i))
		{
			ret->Token[i] = CopyStr(tmp);
		}
	}
	FreePack(p);

	return ret;
}