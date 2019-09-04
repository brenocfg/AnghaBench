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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  ICMP_RESULT ;

/* Variables and functions */

ICMP_RESULT *IcmpApiEchoSend(IP *dest_ip, UCHAR ttl, UCHAR *data, UINT size, UINT timeout)
{
#ifdef	OS_WIN32
	// Validate arguments
	if (dest_ip == NULL || IsIP4(dest_ip) == false || (size != 0 && data == NULL))
	{
		return NULL;
	}
	if (ttl == 0)
	{
		ttl = 127;
	}

	if (IsIcmpApiSupported())
	{
		HANDLE h;
		DWORD dw;
		IPAddr dest_addr;
		UINT reply_size;
		ICMP_ECHO_REPLY *reply;
		ICMP_RESULT *ret = NULL;
		IP_OPTION_INFORMATION opt;

		h = w32net->IcmpCreateFile();

		if (h == INVALID_HANDLE_VALUE)
		{
			return NULL;
		}

		Zero(&opt, sizeof(opt));
		opt.Ttl = ttl;

		IPToInAddr((struct in_addr *)&dest_addr, dest_ip);

		reply_size = sizeof(*reply) + size + 64;
		reply = ZeroMalloc(reply_size);

		dw = w32net->IcmpSendEcho(h, dest_addr, data, size, &opt, reply, reply_size, timeout);

		ret = ZeroMalloc(sizeof(ICMP_RESULT));

		if (dw >= 1 && reply->Status == IP_SUCCESS)
		{
			ret->Ok = true;
		}
		else
		{
			switch (reply->Status)
			{
			case IP_DEST_NET_UNREACHABLE:
				ret->Type = ICMP_TYPE_DESTINATION_UNREACHABLE;
				ret->Code = ICMP_CODE_NET_UNREACHABLE;
				break;

			case IP_DEST_HOST_UNREACHABLE:
				ret->Type = ICMP_TYPE_DESTINATION_UNREACHABLE;
				ret->Code = ICMP_CODE_HOST_UNREACHABLE;
				break;

			case IP_DEST_PROT_UNREACHABLE:
				ret->Type = ICMP_TYPE_DESTINATION_UNREACHABLE;
				ret->Code = ICMP_CODE_PROTOCOL_UNREACHABLE;
				break;

			case IP_DEST_PORT_UNREACHABLE:
				ret->Type = ICMP_TYPE_DESTINATION_UNREACHABLE;
				ret->Code = ICMP_CODE_PORT_UNREACHABLE;
				break;

			case IP_TTL_EXPIRED_TRANSIT:
				ret->Type = ICMP_TYPE_TIME_EXCEEDED;
				ret->Code = ICMP_CODE_TTL_EXCEEDED_IN_TRANSIT;
				break;

			case IP_TTL_EXPIRED_REASSEM:
				ret->Type = ICMP_TYPE_TIME_EXCEEDED;
				ret->Code = ICMP_CODE_FRAGMENT_REASSEMBLY_TIME_EXCEEDED;
				break;

			default:
				ret->Timeout = true;
				break;
			}
		}

		if (ret->Timeout == false)
		{
			ret->Ttl = reply->Options.Ttl;
			ret->Rtt = reply->RoundTripTime;
			InAddrToIP(&ret->IpAddress, (struct in_addr *)&reply->Address);

			if (reply->DataSize >= 1 && reply->Data != NULL)
			{
				ret->DataSize = reply->DataSize;
				ret->Data = Clone(reply->Data, reply->DataSize);
			}
		}

		Free(reply);

		w32net->IcmpCloseHandle(h);

		return ret;
	}
	else
	{
		return NULL;
	}

#else	// OS_WIN32
	return NULL;
#endif	// OS_WIN32
}