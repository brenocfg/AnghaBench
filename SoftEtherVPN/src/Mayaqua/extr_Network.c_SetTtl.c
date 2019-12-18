#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int IsTtlSupported; scalar_t__ CurrentTtl; scalar_t__ IPv6; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ SOCK ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 scalar_t__ IPV6_UNICAST_HOPS ; 
 scalar_t__ IP_TTL ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

bool SetTtl(SOCK *sock, UINT ttl)
{
	DWORD dw;
	int size;
	UINT opt_value = 0;
	// Validate arguments
	if (sock == NULL)
	{
		return false;
	}

	if (sock->IsTtlSupported == false)
	{
		return false;
	}

	if (sock->CurrentTtl == ttl)
	{
		return true;
	}

	dw = ttl;
	size = sizeof(DWORD);

	if (sock->IPv6)
	{
#ifdef	IPV6_UNICAST_HOPS
		opt_value = IPV6_UNICAST_HOPS;
#endif	// IPV6_UNICAST_HOPS
	}
	else
	{
#ifdef	IP_TTL
		opt_value = IP_TTL;
#endif	// IP_TTL
	}

	if (opt_value == 0 ||
		setsockopt(sock->socket, (sock->IPv6 ? IPPROTO_IPV6 : IPPROTO_IP), opt_value, (char *)&dw, size) == false)
	{
		return false;
	}

	sock->CurrentTtl = ttl;

	return true;
}