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
struct TYPE_7__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  InternetSetting; int /*<<< orphan*/  AzureCertHash; int /*<<< orphan*/  CurrentAzureSignature; int /*<<< orphan*/  CurrentAzureTimestamp; int /*<<< orphan*/  CurrentAzureIp; int /*<<< orphan*/  CurrentIPv6; int /*<<< orphan*/  CurrentIPv4; int /*<<< orphan*/  DnsSuffix; int /*<<< orphan*/  CurrentFqdn; int /*<<< orphan*/  CurrentHostName; int /*<<< orphan*/  Err_IPv6; int /*<<< orphan*/  Err_IPv4; } ;
struct TYPE_6__ {int /*<<< orphan*/  Err_IPv6; int /*<<< orphan*/  ErrStr_IPv6; int /*<<< orphan*/  Err_IPv4; int /*<<< orphan*/  ErrStr_IPv4; int /*<<< orphan*/  InternetSetting; int /*<<< orphan*/  AzureCertHash; int /*<<< orphan*/  CurrentAzureSignature; int /*<<< orphan*/  CurrentAzureTimestamp; int /*<<< orphan*/  CurrentAzureIp; int /*<<< orphan*/  CurrentIPv6; int /*<<< orphan*/  CurrentIPv4; int /*<<< orphan*/  DnsSuffix; int /*<<< orphan*/  CurrentFqdn; int /*<<< orphan*/  CurrentHostName; } ;
typedef  int /*<<< orphan*/  INTERNET_SETTING ;
typedef  TYPE_1__ DDNS_CLIENT_STATUS ;
typedef  TYPE_2__ DDNS_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _E (int /*<<< orphan*/ ) ; 

void DCGetStatus(DDNS_CLIENT *c, DDNS_CLIENT_STATUS *st)
{
	// Validate arguments
	if (c == NULL || st == NULL)
	{
		return;
	}

	Zero(st, sizeof(DDNS_CLIENT_STATUS));

	Lock(c->Lock);
	{
		st->Err_IPv4 = c->Err_IPv4;
		st->Err_IPv6 = c->Err_IPv6;

		StrCpy(st->CurrentHostName, sizeof(st->CurrentHostName), c->CurrentHostName);
		StrCpy(st->CurrentFqdn, sizeof(st->CurrentFqdn), c->CurrentFqdn);
		StrCpy(st->DnsSuffix, sizeof(st->DnsSuffix), c->DnsSuffix);
		StrCpy(st->CurrentIPv4, sizeof(st->CurrentIPv4), c->CurrentIPv4);
		StrCpy(st->CurrentIPv6, sizeof(st->CurrentIPv6), c->CurrentIPv6);

		StrCpy(st->CurrentAzureIp, sizeof(st->CurrentAzureIp), c->CurrentAzureIp);
		st->CurrentAzureTimestamp = c->CurrentAzureTimestamp;
		StrCpy(st->CurrentAzureSignature, sizeof(st->CurrentAzureSignature), c->CurrentAzureSignature);
		StrCpy(st->AzureCertHash, sizeof(st->AzureCertHash), c->AzureCertHash);

		Copy(&st->InternetSetting, &c->InternetSetting, sizeof(INTERNET_SETTING));
	}
	Unlock(c->Lock);

	UniStrCpy(st->ErrStr_IPv4, sizeof(st->ErrStr_IPv4), _E(st->Err_IPv4));
	UniStrCpy(st->ErrStr_IPv6, sizeof(st->ErrStr_IPv6), _E(st->Err_IPv6));
}