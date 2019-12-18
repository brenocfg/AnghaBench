#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  query_string ;
typedef  int UINT ;
struct TYPE_4__ {int JsonRpcAuthed; int /*<<< orphan*/  Listener; int /*<<< orphan*/  Cedar; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_1__ CONNECTION ;
typedef  int /*<<< orphan*/  ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  AdminWebHandleFileRequest (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  AdminWebSendUnauthorized (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int INFINITE ; 
 int /*<<< orphan*/ * JsonRpcAuthLogin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  RemoveDosEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SearchStr (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

void AdminWebProcGet(CONNECTION *c, SOCK *s, HTTP_HEADER *h, char *url_target)
{
	ADMIN *a;
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
		AdminWebSendUnauthorized(s, h);
		return;
	}

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

	Free(a);
}