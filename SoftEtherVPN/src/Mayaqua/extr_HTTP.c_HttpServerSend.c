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
typedef  int /*<<< orphan*/  date_str ;
struct TYPE_4__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDummyValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeHttpHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetHttpDateStr (char*,int,int /*<<< orphan*/ ) ; 
 char* HTTP_CONTENT_TYPE2 ; 
 char* HTTP_KEEP_ALIVE ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 TYPE_1__* PackToBuf (int /*<<< orphan*/ *) ; 
 int PostHttp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64 () ; 

bool HttpServerSend(SOCK *s, PACK *p)
{
	BUF *b;
	bool ret;
	HTTP_HEADER *h;
	char date_str[MAX_SIZE];
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return false;
	}

	CreateDummyValue(p);

	b = PackToBuf(p);
	if (b == NULL)
	{
		return false;
	}

	h = NewHttpHeader("HTTP/1.1", "200", "OK");

	GetHttpDateStr(date_str, sizeof(date_str), SystemTime64());
	AddHttpValue(h, NewHttpValue("Date", date_str));
	AddHttpValue(h, NewHttpValue("Keep-Alive", HTTP_KEEP_ALIVE));
	AddHttpValue(h, NewHttpValue("Connection", "Keep-Alive"));
	AddHttpValue(h, NewHttpValue("Content-Type", HTTP_CONTENT_TYPE2));

	ret = PostHttp(s, h, b->Buf, b->Size);

	FreeHttpHeader(h);
	FreeBuf(b);

	return ret;
}