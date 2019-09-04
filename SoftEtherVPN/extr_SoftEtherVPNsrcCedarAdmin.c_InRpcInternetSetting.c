#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; void* ProxyPort; int /*<<< orphan*/  ProxyHostName; void* ProxyType; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ INTERNET_SETTING ;

/* Variables and functions */
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

void InRpcInternetSetting(INTERNET_SETTING *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	t->ProxyType = PackGetInt(p, "ProxyType");
	PackGetStr(p, "ProxyHostName", t->ProxyHostName, sizeof(t->ProxyHostName));
	t->ProxyPort = PackGetInt(p, "ProxyPort");
	PackGetStr(p, "ProxyUsername", t->ProxyUsername, sizeof(t->ProxyUsername));
	PackGetStr(p, "ProxyPassword", t->ProxyPassword, sizeof(t->ProxyPassword));
	PackGetStr(p, "CustomHttpHeader", t->CustomHttpHeader, sizeof(t->CustomHttpHeader));
}