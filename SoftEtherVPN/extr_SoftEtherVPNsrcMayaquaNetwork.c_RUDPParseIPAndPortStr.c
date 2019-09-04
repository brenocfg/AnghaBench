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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  ipstr ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,void*,int /*<<< orphan*/ ) ; 
 size_t INFINITE ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MIN (size_t,int) ; 
 size_t SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrToIP (int /*<<< orphan*/ *,char*) ; 
 size_t ToInt (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

bool RUDPParseIPAndPortStr(void *data, UINT data_size, IP *ip, UINT *port)
{
	char tmp[MAX_SIZE];
	UINT i;
	char ipstr[MAX_SIZE];
	char *portstr;
	// Validate arguments
	if (data == NULL || ip == NULL || port == NULL)
	{
		return false;
	}

	Zero(tmp, sizeof(tmp));

	Copy(tmp, data, MIN(data_size, sizeof(tmp) - 1));

	if (StartWith(tmp, "IP=") == false)
	{
		return false;
	}

	i = SearchStrEx(tmp, "#", 0, true);
	if (i != INFINITE)
	{
		tmp[i] = 0;
	}

	StrCpy(ipstr, sizeof(ipstr), tmp + 3);

	i = SearchStrEx(ipstr, ",PORT=", 0, true);
	if (i == INFINITE)
	{
		return false;
	}

	ipstr[i] = 0;
	portstr = ipstr + i + 6;

	StrToIP(ip, ipstr);
	*port = ToInt(portstr);

	return true;
}