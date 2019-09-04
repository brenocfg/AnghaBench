#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char) ; 
 scalar_t__ IsIP4 (TYPE_1__*) ; 
 scalar_t__ IsUseAlternativeHostname () ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ *,int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StrLower (char*) ; 
 int /*<<< orphan*/  UDP_NAT_T_SERVER_TAG ; 
 int /*<<< orphan*/  UDP_NAT_T_SERVER_TAG_ALT ; 

void RUDPGetRegisterHostNameByIP(char *dst, UINT size, IP *ip)
{
	char tmp[16];
	// Validate arguments
	if (dst == NULL)
	{
		return;
	}

	if (ip != NULL && IsIP4(ip))
	{
		UCHAR hash[SHA1_SIZE];

		Sha1(hash, ip->addr, 4);
		BinToStr(tmp, sizeof(tmp), hash, 2);
	}
	else
	{
		UCHAR rand[2];
		Rand(rand, 2);
		BinToStr(tmp, sizeof(tmp), rand, 2);
	}

	StrLower(tmp);
	Format(dst, size,
		(IsUseAlternativeHostname() ? UDP_NAT_T_SERVER_TAG_ALT : UDP_NAT_T_SERVER_TAG),
		tmp[2], tmp[3]);


	if (false)
	{
		Debug("Hash Src IP: %r\n"
			  "Hash Dst HN: %s\n",
			  ip,
			  dst);
	}
}