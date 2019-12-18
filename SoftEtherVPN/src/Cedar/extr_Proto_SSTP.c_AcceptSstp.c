#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  date_str ;
struct TYPE_3__ {int /*<<< orphan*/  Cedar; int /*<<< orphan*/ * FirstSock; } ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeHttpHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetHttpDateStr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  JoinSockToSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 int PostHttp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ProcessSstpHttps (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64 () ; 

bool AcceptSstp(CONNECTION *c)
{
	SOCK *s;
	HTTP_HEADER *h;
	char date_str[MAX_SIZE];
	bool ret;
	bool ret2 = false;
	SOCK_EVENT *se;
	// Validate arguments
	if (c == NULL)
	{
		return false;
	}

	s = c->FirstSock;

	GetHttpDateStr(date_str, sizeof(date_str), SystemTime64());

	// Return a response
	h = NewHttpHeader("HTTP/1.1", "200", "OK");
	AddHttpValue(h, NewHttpValue("Content-Length", "18446744073709551615"));
	AddHttpValue(h, NewHttpValue("Server", "Microsoft-HTTPAPI/2.0"));
	AddHttpValue(h, NewHttpValue("Date", date_str));

	ret = PostHttp(s, h, NULL, 0);

	FreeHttpHeader(h);

	if (ret)
	{
		SetTimeout(s, INFINITE);

		se = NewSockEvent();

		JoinSockToSockEvent(s, se);

		Debug("ProcessSstpHttps Start.\n");
		ret2 = ProcessSstpHttps(c->Cedar, s, se);
		Debug("ProcessSstpHttps End.\n");

		ReleaseSockEvent(se);
	}

	Disconnect(s);

	return ret2;
}