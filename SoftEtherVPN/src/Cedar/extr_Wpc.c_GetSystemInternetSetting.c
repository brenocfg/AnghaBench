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
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ ProxyPort; int /*<<< orphan*/  ProxyHostName; void* ProxyType; } ;
typedef  TYPE_1__ INTERNET_SETTING ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ GetProxyServerNameAndPortFromIeProxyRegStr (char*,int,scalar_t__*,char*,char*) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  MAX_HOST_NAME_LEN ; 
 int MsRegReadInt (int /*<<< orphan*/ ,char*,char*) ; 
 char* MsRegReadStr (int /*<<< orphan*/ ,char*,char*) ; 
 void* PROXY_HTTP ; 
 void* PROXY_SOCKS ; 
 scalar_t__ ParseHostPort (char*,char**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CURRENT_USER ; 
 scalar_t__ SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void GetSystemInternetSetting(INTERNET_SETTING *setting)
{
#ifdef	OS_WIN32
	bool use_proxy;
	// Validate arguments
	if (setting == NULL)
	{
		return;
	}

	Zero(setting, sizeof(INTERNET_SETTING));

	use_proxy = MsRegReadInt(REG_CURRENT_USER,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
		"ProxyEnable");

	if (use_proxy)
	{
		char *str = MsRegReadStr(REG_CURRENT_USER,
			"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
			"ProxyServer");
		if (str != NULL)
		{
			char name[MAX_HOST_NAME_LEN + 1];
			UINT port;

			if (GetProxyServerNameAndPortFromIeProxyRegStr(name, sizeof(name),
				&port, str, "https"))
			{
				setting->ProxyType = PROXY_HTTP;
				StrCpy(setting->ProxyHostName, sizeof(setting->ProxyHostName), name);
				setting->ProxyPort = port;
			}
			else if (GetProxyServerNameAndPortFromIeProxyRegStr(name, sizeof(name),
				&port, str, "http"))
			{
				setting->ProxyType = PROXY_HTTP;
				StrCpy(setting->ProxyHostName, sizeof(setting->ProxyHostName), name);
				setting->ProxyPort = port;
			}
			else if (GetProxyServerNameAndPortFromIeProxyRegStr(name, sizeof(name),
				&port, str, "socks"))
			{
				setting->ProxyType = PROXY_SOCKS;
				StrCpy(setting->ProxyHostName, sizeof(setting->ProxyHostName), name);
				setting->ProxyPort = port;
			}
			else
			{
				if (SearchStrEx(str, "=", 0, false) == INFINITE)
				{
					char *host;
					UINT port;
					if (ParseHostPort(str, &host, &port, 0))
					{
						if (port != 0)
						{
							setting->ProxyType = PROXY_HTTP;
							StrCpy(setting->ProxyHostName, sizeof(setting->ProxyHostName), host);
							setting->ProxyPort = port;
						}
						Free(host);
					}
				}
			}

			Free(str);
		}
	}
#else	// OS_WIN32
	Zero(setting, sizeof(INTERNET_SETTING));
#endif	// OS_WIN32
}