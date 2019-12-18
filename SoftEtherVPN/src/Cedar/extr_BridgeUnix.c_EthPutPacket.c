#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msghdr {int msg_iovlen; scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {int iov_len; void* iov_base; } ;
typedef  int UINT ;
struct TYPE_4__ {int Socket; int /*<<< orphan*/  Pcap; int /*<<< orphan*/ * Tap; scalar_t__ IsRawIpMode; } ;
typedef  TYPE_1__ ETH ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int,int,...) ; 
 int /*<<< orphan*/  EthPutPacketLinuxIpRaw (TYPE_1__*,void*,int) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int INVALID_SOCKET ; 
 int MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  VLanPutPacket (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  errno ; 
 int pcap_inject (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pcap_perror (int /*<<< orphan*/ ,char*) ; 
 int sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int write (int,void*,int) ; 

void EthPutPacket(ETH *e, void *data, UINT size)
{
	int s, ret;
	// Validate arguments
	if (e == NULL || data == NULL)
	{
		return;
	}
	if (e->IsRawIpMode)
	{
		EthPutPacketLinuxIpRaw(e, data, size);
		return;
	}
	if (size < 14 || size > MAX_PACKET_SIZE)
	{
		Free(data);
		return;
	}

	if (e->Tap != NULL)
	{
#ifndef	NO_VLAN
		// tap mode
		VLanPutPacket(e->Tap, data, size);
#endif	// NO_VLAN
		return;
	}

	s = e->Socket;

	if (s == INVALID_SOCKET)
	{
		Free(data);
		return;
	}

	// Send to device
#ifdef BRIDGE_PCAP
	ret = pcap_inject(e->Pcap, data, size);
	if( ret == -1 ){
#ifdef _DEBUG
		pcap_perror(e->Pcap, "inject");
#endif // _DEBUG
		Debug("EthPutPacket: ret:%d size:%d\n", ret, size);
	}
#else // BRIDGE_PCAP
#ifndef	UNIX_LINUX
	ret = write(s, data, size);
	if (ret<0)
	{
		Debug("EthPutPacket: ret:%d errno:%d  size:%d\n", ret, errno, size);
	}
#else	// UNIX_LINUX
	{
		struct iovec msg_iov;
		struct msghdr msg_header;

		msg_iov.iov_base = data;
		msg_iov.iov_len = size;

		msg_header.msg_name = NULL;
		msg_header.msg_namelen = 0;
		msg_header.msg_iov = &msg_iov;
		msg_header.msg_iovlen = 1;
		msg_header.msg_control = NULL;
		msg_header.msg_controllen = 0;
		msg_header.msg_flags = 0;

		ret = sendmsg(s, &msg_header, 0);

		if (ret<0)
		{
			Debug("EthPutPacket: ret:%d errno:%d  size:%d\n", ret, errno, size);
		}
	}
#endif	// UNIX_LINUX
#endif //BRIDGE_PCAP

	Free(data);
}