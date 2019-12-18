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
struct TYPE_3__ {scalar_t__ ProxyType; int /*<<< orphan*/  ProxyHostName; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ INTERNET_SETTING ;

/* Variables and functions */
 int GetIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsIPMyHost (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIPPrivate (int /*<<< orphan*/ *) ; 
 scalar_t__ IsLocalHostIP (int /*<<< orphan*/ *) ; 
 scalar_t__ PROXY_DIRECT ; 

bool IsProxyPrivateIp(INTERNET_SETTING *s)
{
	IP ip;
	// Validate arguments
	if (s == NULL)
	{
		return false;
	}

	if (s->ProxyType == PROXY_DIRECT)
	{
		return false;
	}

	if (GetIP(&ip, s->ProxyHostName) == false)
	{
		return false;
	}

	if (IsIPPrivate(&ip))
	{
		return true;
	}

	if (IsIPMyHost(&ip))
	{
		return true;
	}

	if (IsLocalHostIP(&ip))
	{
		return true;
	}

	return false;
}