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
typedef  int /*<<< orphan*/  VH ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  DnsProxy (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,scalar_t__) ; 
 scalar_t__ NAT_DNS_PROXY_PORT ; 

void UdpRecvForMe(VH *v, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port, void *data, UINT size)
{
	// Validate arguments
	if (data == NULL || v == NULL)
	{
		return;
	}

	if (dest_port == NAT_DNS_PROXY_PORT)
	{
		// DNS proxy start
		DnsProxy(v, src_ip, src_port, dest_ip, dest_port, data, size);
	}
}