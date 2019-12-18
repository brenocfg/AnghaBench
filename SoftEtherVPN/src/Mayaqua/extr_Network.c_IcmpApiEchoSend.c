#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_15__ {scalar_t__ (* IcmpCreateFile ) () ;int (* IcmpSendEcho ) (scalar_t__,int /*<<< orphan*/ ,int*,scalar_t__,TYPE_2__*,TYPE_4__*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* IcmpCloseHandle ) (scalar_t__) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  Ttl; } ;
struct TYPE_14__ {int Status; int DataSize; int /*<<< orphan*/ * Data; int /*<<< orphan*/  Address; int /*<<< orphan*/  RoundTripTime; TYPE_1__ Options; } ;
struct TYPE_13__ {int Ok; int Timeout; int DataSize; int /*<<< orphan*/  Data; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  Rtt; int /*<<< orphan*/  Ttl; int /*<<< orphan*/  Code; void* Type; } ;
struct TYPE_12__ {int Ttl; } ;
typedef  TYPE_2__ IP_OPTION_INFORMATION ;
typedef  int /*<<< orphan*/  IPAddr ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ ICMP_RESULT ;
typedef  TYPE_4__ ICMP_ECHO_REPLY ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (TYPE_4__*) ; 
 int /*<<< orphan*/  ICMP_CODE_FRAGMENT_REASSEMBLY_TIME_EXCEEDED ; 
 int /*<<< orphan*/  ICMP_CODE_HOST_UNREACHABLE ; 
 int /*<<< orphan*/  ICMP_CODE_NET_UNREACHABLE ; 
 int /*<<< orphan*/  ICMP_CODE_PORT_UNREACHABLE ; 
 int /*<<< orphan*/  ICMP_CODE_PROTOCOL_UNREACHABLE ; 
 int /*<<< orphan*/  ICMP_CODE_TTL_EXCEEDED_IN_TRANSIT ; 
 void* ICMP_TYPE_DESTINATION_UNREACHABLE ; 
 void* ICMP_TYPE_TIME_EXCEEDED ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IPToInAddr (struct in_addr*,int /*<<< orphan*/ *) ; 
#define  IP_DEST_HOST_UNREACHABLE 133 
#define  IP_DEST_NET_UNREACHABLE 132 
#define  IP_DEST_PORT_UNREACHABLE 131 
#define  IP_DEST_PROT_UNREACHABLE 130 
 int IP_SUCCESS ; 
#define  IP_TTL_EXPIRED_REASSEM 129 
#define  IP_TTL_EXPIRED_TRANSIT 128 
 int /*<<< orphan*/  InAddrToIP (int /*<<< orphan*/ *,struct in_addr*) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIcmpApiSupported () ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 
 scalar_t__ stub1 () ; 
 int stub2 (scalar_t__,int /*<<< orphan*/ ,int*,scalar_t__,TYPE_2__*,TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 TYPE_5__* w32net ; 

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