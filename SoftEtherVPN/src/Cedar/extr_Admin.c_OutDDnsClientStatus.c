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
struct TYPE_3__ {int /*<<< orphan*/  ErrStr_IPv6; int /*<<< orphan*/  ErrStr_IPv4; int /*<<< orphan*/  CurrentIPv6; int /*<<< orphan*/  CurrentIPv4; int /*<<< orphan*/  DnsSuffix; int /*<<< orphan*/  CurrentFqdn; int /*<<< orphan*/  CurrentHostName; int /*<<< orphan*/  Err_IPv6; int /*<<< orphan*/  Err_IPv4; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ DDNS_CLIENT_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutDDnsClientStatus(PACK *p, DDNS_CLIENT_STATUS *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "Err_IPv4", t->Err_IPv4);
	PackAddInt(p, "Err_IPv6", t->Err_IPv6);
	PackAddStr(p, "CurrentHostName", t->CurrentHostName);
	PackAddStr(p, "CurrentFqdn", t->CurrentFqdn);
	PackAddStr(p, "DnsSuffix", t->DnsSuffix);
	PackAddStr(p, "CurrentIPv4", t->CurrentIPv4);
	PackAddStr(p, "CurrentIPv6", t->CurrentIPv6);
	PackAddUniStr(p, "ErrStr_IPv4", t->ErrStr_IPv4);
	PackAddUniStr(p, "ErrStr_IPv6", t->ErrStr_IPv6);
}