#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  crypt_name ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_20__ {int /*<<< orphan*/  Now; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * Interrupts; int /*<<< orphan*/  ClientId; } ;
struct TYPE_19__ {TYPE_6__* EtherIP; int /*<<< orphan*/  ClientId; int /*<<< orphan*/  IsEtherIPOnIPsecTunnelMode; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIP; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIP; TYPE_3__* CurrentIpSecSaRecv; } ;
struct TYPE_18__ {int /*<<< orphan*/  Now; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/ * Interrupts; int /*<<< orphan*/  CurrentEtherId; int /*<<< orphan*/  IPsec; int /*<<< orphan*/  Cedar; } ;
struct TYPE_16__ {int CryptoKeySize; TYPE_1__* Crypto; } ;
struct TYPE_17__ {TYPE_2__ TransformSetting; } ;
struct TYPE_15__ {int /*<<< orphan*/  BlockSize; int /*<<< orphan*/  Name; } ;
typedef  TYPE_4__ IKE_SERVER ;
typedef  TYPE_5__ IKE_CLIENT ;
typedef  TYPE_6__ ETHERIP_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IKE_MAX_BLOCK_SIZE ; 
 int /*<<< orphan*/  IPsecLog (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 TYPE_6__* NewEtherIPServer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEtherIPServerSockEvent (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

void IPsecIkeClientManageEtherIPServer(IKE_SERVER *ike, IKE_CLIENT *c)
{
	ETHERIP_SERVER *s;
	// Validate arguments
	if (ike == NULL || c == NULL)
	{
		return;
	}

	if (c->EtherIP == NULL)
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

		c->EtherIP = NewEtherIPServer(ike->Cedar, ike->IPsec, ike,
			&c->ClientIP, c->ClientPort,
			&c->ServerIP, c->ServerPort, crypt_name,
			c->IsEtherIPOnIPsecTunnelMode, crypt_block_size, c->ClientId,
			++ike->CurrentEtherId);

		Debug("IKE_CLIENT 0x%X: EtherIP Server Started.\n", c);

		IPsecLog(ike, c, NULL, NULL, NULL, "LI_ETHERIP_SERVER_STARTED", ike->CurrentEtherId);
	}
	else
	{
		StrCpy(c->EtherIP->ClientId, sizeof(c->EtherIP->ClientId), c->ClientId);
	}

	s = c->EtherIP;

	if (s->Interrupts == NULL)
	{
		s->Interrupts = ike->Interrupts;
	}

	if (s->SockEvent == NULL)
	{
		SetEtherIPServerSockEvent(s, ike->SockEvent);
	}

	s->Now = ike->Now;
}