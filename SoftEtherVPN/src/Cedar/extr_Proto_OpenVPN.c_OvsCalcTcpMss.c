#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_10__ {TYPE_2__* CipherEncrypt; TYPE_1__* MdSend; } ;
struct TYPE_9__ {scalar_t__ Protocol; scalar_t__ Mode; int /*<<< orphan*/  ClientIp; } ;
struct TYPE_8__ {int IsNullCipher; scalar_t__ BlockSize; scalar_t__ IvSize; } ;
struct TYPE_7__ {scalar_t__ Size; } ;
typedef  TYPE_3__ OPENVPN_SESSION ;
typedef  int /*<<< orphan*/  OPENVPN_SERVER ;
typedef  TYPE_4__ OPENVPN_CHANNEL ;

/* Variables and functions */
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 int MTU_FOR_PPPOE ; 
 scalar_t__ OPENVPN_MODE_L2 ; 
 scalar_t__ OPENVPN_PROTOCOL_TCP ; 

UINT OvsCalcTcpMss(OPENVPN_SERVER *s, OPENVPN_SESSION *se, OPENVPN_CHANNEL *c)
{
	UINT ret = MTU_FOR_PPPOE;
	// Validate arguments
	if (s == NULL || se == NULL || c == NULL)
	{
		return 0;
	}

	if (c->MdSend == NULL || c->CipherEncrypt == NULL)
	{
		return 0;
	}

	if (se->Protocol == OPENVPN_PROTOCOL_TCP)
	{
		// Calculation is not required for TCP mode
		return 0;
	}

	// IPv4 / IPv6
	if (IsIP4(&se->ClientIp))
	{
		ret -= 20;
	}
	else
	{
		ret -= 40;
	}

	// UDP
	ret -= 8;

	// opcode
	ret -= 1;

	// HMAC
	ret -= c->MdSend->Size;

	// IV
	ret -= c->CipherEncrypt->IvSize;

	// Packet ID
	ret -= 4;

	if (c->CipherEncrypt->IsNullCipher == false)
	{
		// block
		ret -= c->CipherEncrypt->BlockSize;
	}

	if (se->Mode == OPENVPN_MODE_L2)
	{
		// Inner Ethernet Header
		ret -= 14;
	}

	// Inner IPv4
	ret -= 20;

	// Inner TCP
	ret -= 20;

	return ret;
}