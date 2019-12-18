#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rand_seed ;
struct TYPE_5__ {scalar_t__ DhcpIpStart; scalar_t__ DhcpIpEnd; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  Md5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ READ_UINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchDhcpLeaseByIp (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * SearchDhcpPendingLeaseByIp (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_UINT (int /*<<< orphan*/ *,scalar_t__) ; 

UINT GetFreeDhcpIpAddressByRandom(VH *v, UCHAR *mac)
{
	UINT ip_start, ip_end;
	UINT i;
	UINT num_retry;
	// Validate arguments
	if (v == NULL || mac == NULL)
	{
		return 0;
	}

	ip_start = Endian32(v->DhcpIpStart);
	ip_end = Endian32(v->DhcpIpEnd);

	if (ip_start > ip_end)
	{
		return 0;
	}

	num_retry = (ip_end - ip_start + 1) * 2;
	num_retry = MIN(num_retry, 65536 * 2);

	for (i = 0;i < num_retry;i++)
	{
		UCHAR rand_seed[sizeof(UINT) + 6];
		UCHAR hash[16];
		UINT rand_int;
		UINT new_ip;

		WRITE_UINT(&rand_seed[0], i);
		Copy(rand_seed + sizeof(UINT), mac, 6);

		Md5(hash, rand_seed, sizeof(rand_seed));

		rand_int = READ_UINT(hash);

		new_ip = Endian32(ip_start + (rand_int % (ip_end - ip_start + 1)));

		if (SearchDhcpLeaseByIp(v, new_ip) == NULL && SearchDhcpPendingLeaseByIp(v, new_ip) == NULL)
		{
			// A free IP address is found
			return new_ip;
		}
	}

	// There is no free address
	return 0;
}