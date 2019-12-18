#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  date_str ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  Method; } ;
struct TYPE_10__ {char* Data; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ HTTP_VALUE ;
typedef  TYPE_2__ HTTP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeHttpHeader (TYPE_2__*) ; 
 int /*<<< orphan*/  GetHttpDateStr (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* GetHttpValue (TYPE_2__*,char*) ; 
 int MAX_SIZE ; 
 TYPE_2__* NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 int PostHttp (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  ToStr (char*,int /*<<< orphan*/ ) ; 

bool AdminWebSendBody(SOCK *s, UINT status_code, char *status_string, UCHAR *data, UINT data_size, char *content_type, char *add_header_name, char *add_header_value,
					  HTTP_HEADER *request_headers)
{
	HTTP_HEADER *h;
	char date_str[MAX_SIZE];
	char error_code_str[16];
	bool ret = false;
	HTTP_VALUE *origin;
	if (s == NULL || status_string == NULL || (data_size != 0 && data == NULL) || request_headers == NULL)
	{
		return false;
	}
	if (content_type == NULL)
	{
		content_type = "text/html; charset=utf-8";
	}

	ToStr(error_code_str, status_code);
	GetHttpDateStr(date_str, sizeof(date_str), SystemTime64());

	h = NewHttpHeader("HTTP/1.1", error_code_str, status_string);

	if (StrCmpi(request_headers->Method, "OPTIONS") == 0)
	{
		AddHttpValue(h, NewHttpValue("Allow", "OPTIONS, GET, POST"));
	}

	AddHttpValue(h, NewHttpValue("Cache-Control", "no-cache"));
	AddHttpValue(h, NewHttpValue("Content-Type", content_type));
	AddHttpValue(h, NewHttpValue("Date", date_str));
	AddHttpValue(h, NewHttpValue("Connection", "Keep-Alive"));
	AddHttpValue(h, NewHttpValue("Access-Control-Allow-Methods", "OPTIONS,GET,POST"));
	AddHttpValue(h, NewHttpValue("Access-Control-Allow-Headers", "X-VPNADMIN-HUBNAME,X-VPNADMIN-PASSWORD"));
	AddHttpValue(h, NewHttpValue("Access-Control-Allow-Credentials", "true"));

	origin = GetHttpValue(request_headers, "Origin");
	if (origin != NULL)
	{
		AddHttpValue(h, NewHttpValue("Access-Control-Allow-Origin", origin->Data));
	}

	if (add_header_name != NULL && add_header_value != NULL)
	{
		AddHttpValue(h, NewHttpValue(add_header_name, add_header_value));
	}

	ret = PostHttp(s, h, data, data_size);

	FreeHttpHeader(h);

	return ret;
}