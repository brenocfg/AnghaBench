#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url ;
struct TYPE_9__ {char* Buf; } ;
struct TYPE_8__ {int Path; int IsSsl; int Port; char* Method; char* Protocol; char* Referer; char* UserAgent; int /*<<< orphan*/  Hostname; } ;
typedef  TYPE_1__ HTTPLOG ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddLogBufToStr (TYPE_2__*,char*,char*) ; 
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int MAX_SIZE ; 
 TYPE_2__* NewBuf () ; 
 scalar_t__ StartWith (int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,char*,int) ; 

char *BuildHttpLogStr(HTTPLOG *h)
{
	BUF *b;
	char url[MAX_SIZE];
	char nullchar = 0;
	char *ret;
	// Validate arguments
	if (h == NULL)
	{
		return CopyStr("");
	}

	b = NewBuf();

	if (StartWith(h->Path, "http://") || StartWith(h->Path, "https://"))
	{
		StrCpy(url, sizeof(url), h->Path);
	}
	else
	{
		// URL generation
		if (h->IsSsl == false)
		{
			if (h->Port == 80)
			{
				Format(url, sizeof(url), "http://%s%s",
					h->Hostname, h->Path);
			}
			else
			{
				Format(url, sizeof(url), "http://%s:%u%s",
					h->Hostname, h->Port, h->Path);
			}
		}
		else
		{
			if (h->Port == 443)
			{
				Format(url, sizeof(url), "https://%s/",
					h->Hostname);
			}
			else
			{
				Format(url, sizeof(url), "https://%s:%u/",
					h->Hostname, h->Port);
			}
		}
	}

	AddLogBufToStr(b, "HttpMethod", h->Method);
	AddLogBufToStr(b, "HttpUrl", url);
	AddLogBufToStr(b, "HttpProtocol", h->Protocol);
	AddLogBufToStr(b, "HttpReferer", h->Referer);
	AddLogBufToStr(b, "HttpUserAgent", h->UserAgent);

	WriteBuf(b, &nullchar, 1);

	ret = CopyStr(b->Buf);

	FreeBuf(b);

	return ret;
}