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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  server_port ;
struct TYPE_4__ {char* Method; char* Referer; int Secure; char* Target; char* HostName; int Port; char* HeaderHostName; } ;
typedef  TYPE_1__ URL_DATA ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  MAX_HOST_NAME_LEN ; 
 int MAX_SIZE ; 
 int ParseHostPort (char*,char**,scalar_t__*,int) ; 
 scalar_t__ SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 char* WPC_HTTP_GET_NAME ; 
 char* WPC_HTTP_POST_NAME ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool ParseUrl(URL_DATA *data, char *str, bool is_post, char *referrer)
{
	char tmp[MAX_SIZE * 3];
	char server_port[MAX_HOST_NAME_LEN + 16];
	char *s = NULL;
	char *host;
	UINT port;
	UINT i;
	// Validate arguments
	if (data == NULL || str == NULL)
	{
		return false;
	}

	Zero(data, sizeof(URL_DATA));

	if (is_post)
	{
		StrCpy(data->Method, sizeof(data->Method), WPC_HTTP_POST_NAME);
	}
	else
	{
		StrCpy(data->Method, sizeof(data->Method), WPC_HTTP_GET_NAME);
	}

	if (referrer != NULL)
	{
		StrCpy(data->Referer, sizeof(data->Referer), referrer);
	}

	StrCpy(tmp, sizeof(tmp), str);
	Trim(tmp);

	// Determine the protocol
	if (StartWith(tmp, "http://"))
	{
		data->Secure = false;
		s = &tmp[7];
	}
	else if (StartWith(tmp, "https://"))
	{
		data->Secure = true;
		s = &tmp[8];
	}
	else
	{
		if (SearchStrEx(tmp, "://", 0, false) != INFINITE)
		{
			return false;
		}
		data->Secure = false;
		s = &tmp[0];
	}

	// Get the "server name:port number"
	StrCpy(server_port, sizeof(server_port), s);
	i = SearchStrEx(server_port, "/", 0, false);
	if (i != INFINITE)
	{
		server_port[i] = 0;
		s += StrLen(server_port);
		StrCpy(data->Target, sizeof(data->Target), s);
	}
	else
	{
		StrCpy(data->Target, sizeof(data->Target), "/");
	}

	if (ParseHostPort(server_port, &host, &port, data->Secure ? 443 : 80) == false)
	{
		return false;
	}

	StrCpy(data->HostName, sizeof(data->HostName), host);
	data->Port = port;

	Free(host);

	if ((data->Secure && data->Port == 443) || (data->Secure == false && data->Port == 80))
	{
		StrCpy(data->HeaderHostName, sizeof(data->HeaderHostName), data->HostName);
	}
	else
	{
		Format(data->HeaderHostName, sizeof(data->HeaderHostName),
			"%s:%u", data->HostName, data->Port);
	}

	return true;
}