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
struct TYPE_3__ {int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyHostName; int /*<<< orphan*/  ProxyType; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ INTERNET_SETTING ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcInternetSetting(PACK *p, INTERNET_SETTING *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "ProxyType", t->ProxyType);
	PackAddStr(p, "ProxyHostName", t->ProxyHostName);
	PackAddInt(p, "ProxyPort", t->ProxyPort);
	PackAddStr(p, "ProxyUsername", t->ProxyUsername);
	PackAddStr(p, "ProxyPassword", t->ProxyPassword);
	PackAddStr(p, "CustomHttpHeader", t->CustomHttpHeader);
}