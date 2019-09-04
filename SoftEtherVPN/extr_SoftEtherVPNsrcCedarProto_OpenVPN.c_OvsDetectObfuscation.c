#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  OPENVPN_PACKET ;

/* Variables and functions */
 void* Clone (void*,scalar_t__) ; 
 int /*<<< orphan*/  Free (void*) ; 
 scalar_t__ INFINITE ; 
 scalar_t__ OPENVPN_SCRAMBLE_MODE_DISABLED ; 
 scalar_t__ OPENVPN_SCRAMBLE_MODE_OBFUSCATE ; 
 scalar_t__ OPENVPN_SCRAMBLE_MODE_REVERSE ; 
 scalar_t__ OPENVPN_SCRAMBLE_MODE_XORMASK ; 
 scalar_t__ OPENVPN_SCRAMBLE_MODE_XORPTRPOS ; 
 int /*<<< orphan*/  OvsDataReverse (void*,scalar_t__) ; 
 int /*<<< orphan*/  OvsDataXorMask (void*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OvsDataXorPtrPos (void*,scalar_t__) ; 
 int /*<<< orphan*/  OvsFreePacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OvsParsePacket (void*,scalar_t__) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

UINT OvsDetectObfuscation(void *data, UINT size, char *xormask)
{
	UINT ret;
	void *tmp;
	OPENVPN_PACKET *parsed_packet;
	// Validate arguments
	if (data == NULL || size == 0)
	{
		return INFINITE;
	}

	ret = INFINITE;
	tmp = NULL;

	// OPENVPN_SCRAMBLE_MODE_DISABLED
	parsed_packet = OvsParsePacket(data, size);
	if (parsed_packet != NULL)
	{
		ret = OPENVPN_SCRAMBLE_MODE_DISABLED;
		goto final;
	}

	// OPENVPN_SCRAMBLE_MODE_XORMASK
	tmp = Clone(data, size);

	OvsDataXorMask(tmp, size, xormask, StrLen(xormask));

	parsed_packet = OvsParsePacket(tmp, size);
	if (parsed_packet != NULL)
	{
		ret = OPENVPN_SCRAMBLE_MODE_XORMASK;
		goto final;
	}

	Free(tmp);

	// OPENVPN_SCRAMBLE_MODE_XORPTRPOS
	tmp = Clone(data, size);

	OvsDataXorPtrPos(tmp, size);

	parsed_packet = OvsParsePacket(tmp, size);
	if (parsed_packet != NULL)
	{
		ret = OPENVPN_SCRAMBLE_MODE_XORPTRPOS;
		goto final;
	}

	Free(tmp);

	// OPENVPN_SCRAMBLE_MODE_REVERSE
	tmp = Clone(data, size);

	OvsDataReverse(tmp, size);

	parsed_packet = OvsParsePacket(tmp, size);
	if (parsed_packet != NULL)
	{
		ret = OPENVPN_SCRAMBLE_MODE_REVERSE;
		goto final;
	}

	Free(tmp);

	// OPENVPN_SCRAMBLE_MODE_OBFUSCATE
	tmp = Clone(data, size);

	OvsDataXorMask(tmp, size, xormask, StrLen(xormask));
	OvsDataXorPtrPos(tmp, size);
	OvsDataReverse(tmp, size);
	OvsDataXorPtrPos(tmp, size);

	parsed_packet = OvsParsePacket(tmp, size);
	if (parsed_packet != NULL)
	{
		ret = OPENVPN_SCRAMBLE_MODE_OBFUSCATE;
		goto final;
	}

final:
	OvsFreePacket(parsed_packet);
	Free(tmp);
	return ret;
}