#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ip_str ;
typedef  int /*<<< orphan*/  date_str ;
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDummyValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeHttpHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetHttpDateStr (char*,int,int /*<<< orphan*/ ) ; 
 char* HTTP_CONTENT_TYPE2 ; 
 char* HTTP_KEEP_ALIVE ; 
 int /*<<< orphan*/  HTTP_VPN_TARGET ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewHttpHeader (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 TYPE_2__* PackToBuf (int /*<<< orphan*/ *) ; 
 int PostHttp (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64 () ; 

bool HttpClientSend(SOCK *s, PACK *p)
{
	BUF *b;
	bool ret;
	HTTP_HEADER *h;
	char date_str[MAX_SIZE];
	char ip_str[MAX_SIZE];

	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return false;
	}

	IPToStr(ip_str, sizeof(ip_str), &s->RemoteIP);

	CreateDummyValue(p);

	b = PackToBuf(p);
	if (b == NULL)
	{
		return false;
	}

	h = NewHttpHeader("POST", HTTP_VPN_TARGET, "HTTP/1.1");

	GetHttpDateStr(date_str, sizeof(date_str), SystemTime64());
	AddHttpValue(h, NewHttpValue("Date", date_str));
	AddHttpValue(h, NewHttpValue("Host", ip_str));
	AddHttpValue(h, NewHttpValue("Keep-Alive", HTTP_KEEP_ALIVE));
	AddHttpValue(h, NewHttpValue("Connection", "Keep-Alive"));
	AddHttpValue(h, NewHttpValue("Content-Type", HTTP_CONTENT_TYPE2));

	ret = PostHttp(s, h, b->Buf, b->Size);

	FreeHttpHeader(h);
	FreeBuf(b);

	return ret;
}