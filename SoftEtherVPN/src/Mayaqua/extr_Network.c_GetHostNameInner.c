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
struct sockaddr_in {scalar_t__ sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_len; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  ip_str ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,struct in_addr*,int) ; 
 int GetHostNameInner6 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  IPToInAddr (struct in_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Zero (struct sockaddr_in*,int) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool GetHostNameInner(char *hostname, UINT size, IP *ip)
{
	struct in_addr addr;
	struct sockaddr_in sa;
	char tmp[MAX_SIZE];
	char ip_str[64];
	// Validate arguments
	if (hostname == NULL || ip == NULL)
	{
		return false;
	}

	if (IsIP6(ip))
	{
		return GetHostNameInner6(hostname, size, ip);
	}

	// Reverse resolution
	IPToInAddr(&addr, ip);
	Zero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;

#if	defined(UNIX_BSD) || defined(UNIX_MACOS)
	sa.sin_len = INET_ADDRSTRLEN;
#endif	// UNIX_BSD || UNIX_MACOS

	Copy(&sa.sin_addr, &addr, sizeof(struct in_addr));
	sa.sin_port = 0;

	if (getnameinfo((struct sockaddr *)&sa, sizeof(sa), tmp, sizeof(tmp), NULL, 0, 0) != 0)
	{
		return false;
	}

	IPToStr(ip_str, sizeof(ip_str), ip);

	if (StrCmpi(tmp, ip_str) == 0)
	{
		return false;
	}

	if (IsEmptyStr(tmp))
	{
		return false;
	}

	StrCpy(hostname, size, tmp);

	return true;
}