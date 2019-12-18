#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  crypt_name ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_25__ {int L2TPv3; int /*<<< orphan*/  Now; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * Interrupts; int /*<<< orphan*/  ClientId; int /*<<< orphan*/  VendorName; } ;
struct TYPE_24__ {int /*<<< orphan*/  ClientId; int /*<<< orphan*/  IsL2TPOnIPsecTunnelMode; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIP; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIP; TYPE_3__* CurrentIpSecSaRecv; } ;
struct TYPE_23__ {int /*<<< orphan*/  CurrentEtherId; int /*<<< orphan*/  IPsec; int /*<<< orphan*/  Cedar; } ;
struct TYPE_22__ {int /*<<< orphan*/  Now; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/ * Interrupts; TYPE_8__* IkeClient; TYPE_7__* IkeServer; } ;
struct TYPE_21__ {TYPE_9__* EtherIP; TYPE_4__* Tunnel; } ;
struct TYPE_20__ {int /*<<< orphan*/  VendorName; } ;
struct TYPE_18__ {int CryptoKeySize; TYPE_1__* Crypto; } ;
struct TYPE_19__ {TYPE_2__ TransformSetting; } ;
struct TYPE_17__ {int /*<<< orphan*/  BlockSize; int /*<<< orphan*/  Name; } ;
typedef  TYPE_5__ L2TP_SESSION ;
typedef  TYPE_6__ L2TP_SERVER ;
typedef  TYPE_7__ IKE_SERVER ;
typedef  TYPE_8__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,TYPE_8__*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IKE_MAX_BLOCK_SIZE ; 
 int /*<<< orphan*/  IPsecLog (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 TYPE_9__* NewEtherIPServer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEtherIPServerSockEvent (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

void L2TPSessionManageEtherIPServer(L2TP_SERVER *l2tp, L2TP_SESSION *s)
{
	IKE_SERVER *ike;
	IKE_CLIENT *c;
	// Validate arguments
	if (l2tp == NULL || s == NULL)
	{
		return;
	}

	if (l2tp->IkeClient == NULL || l2tp->IkeServer == NULL)
	{
		return;
	}

	ike = l2tp->IkeServer;
	c = l2tp->IkeClient;

	if (s->EtherIP == NULL)
	{
		char crypt_name[MAX_SIZE];
		UINT crypt_block_size = IKE_MAX_BLOCK_SIZE;

		Zero(crypt_name, sizeof(crypt_name));

		if (c->CurrentIpSecSaRecv != NULL)
		{
			Format(crypt_name, sizeof(crypt_name),
				"IPsec - %s (%u bits)",
				c->CurrentIpSecSaRecv->TransformSetting.Crypto->Name,
				c->CurrentIpSecSaRecv->TransformSetting.CryptoKeySize * 8);

			crypt_block_size = c->CurrentIpSecSaRecv->TransformSetting.Crypto->BlockSize;
		}

		s->EtherIP = NewEtherIPServer(ike->Cedar, ike->IPsec, ike,
			&c->ClientIP, c->ClientPort,
			&c->ServerIP, c->ServerPort, crypt_name,
			c->IsL2TPOnIPsecTunnelMode, crypt_block_size, c->ClientId,
			++ike->CurrentEtherId);

		StrCpy(s->EtherIP->VendorName, sizeof(s->EtherIP->VendorName), s->Tunnel->VendorName);

		s->EtherIP->L2TPv3 = true;

		Debug("IKE_CLIENT 0x%X: EtherIP Server Started.\n", c);

		IPsecLog(ike, c, NULL, NULL, NULL, "LI_ETHERIP_SERVER_STARTED", ike->CurrentEtherId);
	}
	else
	{
		StrCpy(s->EtherIP->ClientId, sizeof(s->EtherIP->ClientId), c->ClientId);
	}

	if (s->EtherIP->Interrupts == NULL)
	{
		s->EtherIP->Interrupts = l2tp->Interrupts;
	}

	if (s->EtherIP->SockEvent == NULL)
	{
		SetEtherIPServerSockEvent(s->EtherIP, l2tp->SockEvent);
	}

	s->EtherIP->Now = l2tp->Now;
}