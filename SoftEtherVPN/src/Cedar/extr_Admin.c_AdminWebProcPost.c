#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  query_string ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {scalar_t__ MaxJsonRpcRecvSize; } ;
typedef  TYPE_1__ UCHAR ;
struct TYPE_22__ {int JsonRpcAuthed; int /*<<< orphan*/  Listener; int /*<<< orphan*/  Cedar; } ;
struct TYPE_21__ {int /*<<< orphan*/  SecureMode; } ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_3__ CONNECTION ;
typedef  TYPE_1__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  AdminWebHandleFileRequest (TYPE_1__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  AdminWebSendUnauthorized (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 scalar_t__ INFINITE ; 
 TYPE_1__* JsonRpcAuthLogin (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 scalar_t__ RecvAll (TYPE_2__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecvAllWithDiscard (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveDosEntry (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ SearchStr (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 TYPE_1__* ZeroMalloc (scalar_t__) ; 

void AdminWebProcPost(CONNECTION *c, SOCK *s, HTTP_HEADER *h, UINT post_data_size, char *url_target)
{
	ADMIN *a;
	UCHAR *data;
	char url[MAX_PATH];
	char query_string[MAX_SIZE];
	UINT i;
	if (c == NULL || s == NULL || h == NULL || url_target == NULL)
	{
		return;
	}

	a = JsonRpcAuthLogin(c->Cedar, s, h);
	if (a == NULL)
	{
		RecvAllWithDiscard(s, post_data_size, s->SecureMode);
		AdminWebSendUnauthorized(s, h);
		return;
	}

	if (post_data_size > a->MaxJsonRpcRecvSize)
	{
		Disconnect(s);
		return;
	}

	data = ZeroMalloc(post_data_size + 1);

	if (RecvAll(s, data, post_data_size, s->SecureMode))
	{
		c->JsonRpcAuthed = true;
#ifndef	GC_SOFTETHER_OSS
		RemoveDosEntry(c->Listener, s);
#endif	// GC_SOFTETHER_OSS

		// Divide url_target into URL and query string
		StrCpy(url, sizeof(url), url_target);
		Zero(query_string, sizeof(query_string));
		i = SearchStr(url, "?", 0);
		if (i != INFINITE)
		{
			StrCpy(query_string, sizeof(query_string), url + i + 1);
			url[i] = 0;
		}

		AdminWebHandleFileRequest(a, c, s, h, url, query_string, "/admin", "|wwwroot/admin");
	}

	Free(data);
	Free(a);
}