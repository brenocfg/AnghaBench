#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;

/* Variables and functions */
 int AdminWebSendBody (int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  ReplaceStrEx (char*,int,char*,char*,char*,int) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int StrSize (char*) ; 
 char* ZeroMalloc (int) ; 

bool AdminWebSend302Redirect(SOCK *s, char *url, char *query_string, HTTP_HEADER *request_headers)
{
	bool ret = false;
	char *txt;
	UINT txt_size;
	char *url2;
	UINT url2_size;
	char *body = "<html><head><title>Object moved</title></head><body>\r\n<h2>Object moved to <a href=\"$URL$\">here</a>.</h2>\r\n</body></html>";
	if (s == NULL || url == NULL || request_headers == NULL)
	{
		return false;
	}

	url2_size = (StrSize(url) + StrSize(query_string) + MAX_SIZE) * 2;
	url2 = ZeroMalloc(url2_size);

	StrCpy(url2, url2_size, url);
	if (IsEmptyStr(query_string) == false)
	{
		StrCat(url2, url2_size, "?");
		StrCat(url2, url2_size, query_string);
	}

	txt_size = (StrSize(body) + StrSize(url2) + MAX_SIZE) * 2;
	txt = ZeroMalloc(txt_size);

	ReplaceStrEx(txt, txt_size, body, "$URL$", url2, false);

	ret = AdminWebSendBody(s, 302, "Found", txt, StrLen(txt), NULL, "Location", url2, request_headers);

	Free(txt);

	Free(url2);

	return ret;
}