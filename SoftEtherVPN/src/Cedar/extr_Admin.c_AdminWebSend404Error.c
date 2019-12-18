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
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;

/* Variables and functions */
 int AdminWebSendBody (int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

bool AdminWebSend404Error(SOCK *s, HTTP_HEADER *request_headers)
{
	char *body = "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\r\n<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>\r\n";
	if (s == NULL || request_headers == NULL)
	{
		return false;
	}

	return AdminWebSendBody(s, 404, "Not Found", body, StrLen(body), NULL, NULL, NULL, request_headers);
}