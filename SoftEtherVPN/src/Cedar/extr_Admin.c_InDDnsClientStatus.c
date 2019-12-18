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
struct TYPE_4__ {int /*<<< orphan*/  ErrStr_IPv6; int /*<<< orphan*/  ErrStr_IPv4; int /*<<< orphan*/  CurrentIPv6; int /*<<< orphan*/  CurrentIPv4; int /*<<< orphan*/  DnsSuffix; int /*<<< orphan*/  CurrentFqdn; int /*<<< orphan*/  CurrentHostName; void* Err_IPv6; void* Err_IPv4; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ DDNS_CLIENT_STATUS ;

/* Variables and functions */
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InDDnsClientStatus(DDNS_CLIENT_STATUS *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(DDNS_CLIENT_STATUS));

	t->Err_IPv4 = PackGetInt(p, "Err_IPv4");
	t->Err_IPv6 = PackGetInt(p, "Err_IPv6");

	PackGetStr(p, "CurrentHostName", t->CurrentHostName, sizeof(t->CurrentHostName));
	PackGetStr(p, "CurrentFqdn", t->CurrentFqdn, sizeof(t->CurrentFqdn));
	PackGetStr(p, "DnsSuffix", t->DnsSuffix, sizeof(t->DnsSuffix));
	PackGetStr(p, "CurrentIPv4", t->CurrentIPv4, sizeof(t->CurrentIPv4));
	PackGetStr(p, "CurrentIPv6", t->CurrentIPv6, sizeof(t->CurrentIPv6));
	PackGetUniStr(p, "ErrStr_IPv4", t->ErrStr_IPv4, sizeof(t->ErrStr_IPv4));
	PackGetUniStr(p, "ErrStr_IPv6", t->ErrStr_IPv6, sizeof(t->ErrStr_IPv6));
}