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
typedef  scalar_t__ USHORT ;
typedef  int UINT ;
struct TYPE_5__ {scalar_t__ Checksum; } ;
typedef  TYPE_1__ IPV4_HEADER ;

/* Variables and functions */
 int IPV4_GET_HEADER_LEN (TYPE_1__*) ; 
 scalar_t__ IpChecksum (TYPE_1__*,int) ; 

bool IpCheckChecksum(IPV4_HEADER *ip)
{
	UINT header_size;
	USHORT checksum_original, checksum_calc;
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}

	header_size = IPV4_GET_HEADER_LEN(ip) * 4;
	checksum_original = ip->Checksum;
	ip->Checksum = 0;
	checksum_calc = IpChecksum(ip, header_size);
	ip->Checksum = checksum_original;

	if (checksum_original == checksum_calc)
	{
		return true;
	}
	else
	{
		return false;
	}
}