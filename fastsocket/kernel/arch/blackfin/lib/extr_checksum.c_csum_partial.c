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
typedef  int __wsum ;

/* Variables and functions */
 scalar_t__ do_csum (void const*,int) ; 

__wsum csum_partial(const void *buff, int len, __wsum sum)
{
	/*
	 * Just in case we get nasty checksum data...
	 * Like 0xffff6ec3 in the case of our IPv6 multicast header.
	 * We fold to begin with, as well as at the end.
	 */
	sum = (sum & 0xffff) + (sum >> 16);

	sum += do_csum(buff, len);

	sum = (sum & 0xffff) + (sum >> 16);

	return sum;
}