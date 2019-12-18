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
struct sockaddr_in6 {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_len; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  ip_str ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  IPToInAddr6 (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Zero (struct sockaddr_in6*,int) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool GetHostNameInner6(char *hostname, UINT size, IP *ip)
{
	struct in6_addr addr;
	struct sockaddr_in6 sa;
	char tmp[MAX_SIZE];
	char ip_str[256];
	// Validate arguments
	if (hostname == NULL || ip == NULL)
	{
		return false;
	}

	// Reverse resolution
	IPToInAddr6(&addr, ip);
	Zero(&sa, sizeof(sa));
	sa.sin6_family = AF_INET6;

#if	defined(UNIX_BSD) || defined(UNIX_MACOS)
	sa.sin6_len = INET6_ADDRSTRLEN;
#endif	// UNIX_BSD || UNIX_MACOS

	Copy(&sa.sin6_addr, &addr, sizeof(struct in6_addr));
	sa.sin6_port = 0;

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