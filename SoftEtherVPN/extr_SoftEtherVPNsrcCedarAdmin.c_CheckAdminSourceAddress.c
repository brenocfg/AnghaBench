#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {int /*<<< orphan*/  RemoteIP; } ;
struct TYPE_6__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ADMINIP_TXT ; 
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 size_t INFINITE ; 
 int /*<<< orphan*/  IPAnd4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPAnd6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ ParseIpAndMask46 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/ * ReadDump (int /*<<< orphan*/ ) ; 
 size_t SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 scalar_t__ StrToIP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool CheckAdminSourceAddress(SOCK *sock, char *hubname)
{
	BUF *b;
	char *s;
	bool ok = false;
	// Validate arguments
	if (sock == NULL)
	{
		return false;
	}

	b = ReadDump(ADMINIP_TXT);
	if (b == NULL)
	{
		return true;
	}

	while (true)
	{
		UINT i;
		TOKEN_LIST *t;
		IP ip;
		IP mask;
		IP ip1;
		IP ip2;
		s = CfgReadNextLine(b);

		if (s == NULL)
		{
			break;
		}

		Trim(s);

		i = SearchStrEx(s, "//", 0, false);
		if (i != INFINITE)
		{
			s[i] = 0;
		}

		i = SearchStrEx(s, "#", 0, false);
		if (i != INFINITE)
		{
			s[i] = 0;
		}

		Trim(s);

		t = ParseToken(s, " \t");
		if (t != NULL)
		{
			if (t->NumTokens >= 1)
			{
				if (t->NumTokens == 1 || StrCmpi(hubname, t->Token[1]) == 0)
				{
					if (ParseIpAndMask46(t->Token[0], &ip, &mask))
					{
						if (IsIP4(&sock->RemoteIP) && IsIP4(&ip))
						{
							IPAnd4(&ip1, &sock->RemoteIP, &mask);
							IPAnd4(&ip2, &ip, &mask);

							if (CmpIpAddr(&ip1, &ip2) == 0)
							{
								ok = true;
							}
						}
						else if (IsIP6(&sock->RemoteIP) && IsIP6(&ip))
						{
							IPAnd6(&ip1, &sock->RemoteIP, &mask);
							IPAnd6(&ip2, &ip, &mask);

							if (CmpIpAddr(&ip1, &ip2) == 0)
							{
								ok = true;
							}
						}
					}
					else if (StrToIP(&ip, t->Token[0]))
					{
						if (CmpIpAddr(&sock->RemoteIP, &ip) == 0)
						{
							ok = true;
						}
					}

					if (StrCmpi(t->Token[0], "*") == 0)
					{
						ok = true;
					}
				}
			}

			FreeToken(t);
		}

		Free(s);
	}

	FreeBuf(b);

	return ok;
}