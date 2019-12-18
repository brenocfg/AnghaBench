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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_20__ {TYPE_4__* L2TP; TYPE_3__* CurrentIpSecSaRecv; int /*<<< orphan*/  ClientIP; int /*<<< orphan*/  L2TPClientIP; int /*<<< orphan*/  ServerIP; int /*<<< orphan*/  L2TPServerIP; } ;
struct TYPE_19__ {int /*<<< orphan*/  Now; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/ * Interrupts; int /*<<< orphan*/  Cedar; } ;
struct TYPE_18__ {int /*<<< orphan*/  Now; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * Interrupts; int /*<<< orphan*/  CryptName; TYPE_6__* IkeClient; } ;
struct TYPE_16__ {int CryptoKeySize; TYPE_1__* Crypto; } ;
struct TYPE_17__ {TYPE_2__ TransformSetting; } ;
struct TYPE_15__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  BlockSize; } ;
typedef  TYPE_4__ L2TP_SERVER ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_5__ IKE_SERVER ;
typedef  TYPE_6__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,TYPE_6__*) ; 
 int /*<<< orphan*/  Format (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IKE_MAX_BLOCK_SIZE ; 
 int /*<<< orphan*/  IPsecLog (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IsIP6 (int /*<<< orphan*/ *) ; 
 TYPE_4__* NewL2TPServerEx (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetL2TPServerSockEvent (TYPE_4__*,int /*<<< orphan*/ ) ; 

void IPsecIkeClientManageL2TPServer(IKE_SERVER *ike, IKE_CLIENT *c)
{
	L2TP_SERVER *l2tp;
	// Validate arguments
	if (ike == NULL || c == NULL)
	{
		return;
	}

	if (c->L2TP == NULL)
	{
		UINT crypt_block_size = IKE_MAX_BLOCK_SIZE;

		if (c->CurrentIpSecSaRecv != NULL)
		{
			crypt_block_size = c->CurrentIpSecSaRecv->TransformSetting.Crypto->BlockSize;
		}

		c->L2TP = NewL2TPServerEx(ike->Cedar, ike, IsIP6(&c->ClientIP), crypt_block_size);
		c->L2TP->IkeClient = c;

		Copy(&c->L2TPServerIP, &c->ServerIP, sizeof(IP));
		Copy(&c->L2TPClientIP, &c->ClientIP, sizeof(IP));

		if (c->CurrentIpSecSaRecv != NULL)
		{
			Format(c->L2TP->CryptName, sizeof(c->L2TP->CryptName),
				"IPsec - %s (%u bits)",
				c->CurrentIpSecSaRecv->TransformSetting.Crypto->Name,
				c->CurrentIpSecSaRecv->TransformSetting.CryptoKeySize * 8);
		}

		Debug("IKE_CLIENT 0x%X: L2TP Server Started.\n", c);

		IPsecLog(ike, c, NULL, NULL, "LI_L2TP_SERVER_STARTED");
	}

	l2tp = c->L2TP;

	if (l2tp->Interrupts == NULL)
	{
		l2tp->Interrupts = ike->Interrupts;
	}

	if (l2tp->SockEvent == NULL)
	{
		SetL2TPServerSockEvent(l2tp, ike->SockEvent);
	}

	l2tp->Now = ike->Now;
}