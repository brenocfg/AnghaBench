#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UDPPACKET ;
struct TYPE_8__ {int /*<<< orphan*/  SendPacketList; TYPE_1__* Cedar; } ;
struct TYPE_7__ {int ObfuscationMode; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; } ;
struct TYPE_6__ {int /*<<< orphan*/  OpenVPNObfuscationMask; } ;
typedef  TYPE_2__ OPENVPN_SESSION ;
typedef  TYPE_3__ OPENVPN_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/ * NewUdpPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__) ; 
#define  OPENVPN_SCRAMBLE_MODE_DISABLED 132 
#define  OPENVPN_SCRAMBLE_MODE_OBFUSCATE 131 
#define  OPENVPN_SCRAMBLE_MODE_REVERSE 130 
#define  OPENVPN_SCRAMBLE_MODE_XORMASK 129 
#define  OPENVPN_SCRAMBLE_MODE_XORPTRPOS 128 
 int /*<<< orphan*/  OvsDataReverse (void*,scalar_t__) ; 
 int /*<<< orphan*/  OvsDataXorMask (void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OvsDataXorPtrPos (void*,scalar_t__) ; 
 int /*<<< orphan*/  StrLen (int /*<<< orphan*/ ) ; 

void OvsSendPacketRawNow(OPENVPN_SERVER *s, OPENVPN_SESSION *se, void *data, UINT size)
{
	UDPPACKET *u;

	// Validate arguments
	if (s == NULL || se == NULL || data == NULL || size == 0)
	{
		Free(data);
		return;
	}

	// Scramble the packet
	switch (se->ObfuscationMode)
	{
	case OPENVPN_SCRAMBLE_MODE_DISABLED:
		break;
	case OPENVPN_SCRAMBLE_MODE_XORMASK:
		OvsDataXorMask(data, size, s->Cedar->OpenVPNObfuscationMask, StrLen(s->Cedar->OpenVPNObfuscationMask));
		break;
	case OPENVPN_SCRAMBLE_MODE_XORPTRPOS:
		OvsDataXorPtrPos(data, size);
		break;
	case OPENVPN_SCRAMBLE_MODE_REVERSE:
		OvsDataReverse(data, size);
		break;
	case OPENVPN_SCRAMBLE_MODE_OBFUSCATE:
		OvsDataXorPtrPos(data, size);
		OvsDataReverse(data, size);
		OvsDataXorPtrPos(data, size);
		OvsDataXorMask(data, size, s->Cedar->OpenVPNObfuscationMask, StrLen(s->Cedar->OpenVPNObfuscationMask));
	}

	u = NewUdpPacket(&se->ServerIp, se->ServerPort, &se->ClientIp, se->ClientPort,
		data, size);

	Add(s->SendPacketList, u);
}