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
typedef  int uint32_t ;
struct in_addr {int s_addr; } ;
typedef  int in_addr_t ;

/* Variables and functions */

in_addr_t inet_netof(struct in_addr in)
{
	uint32_t h = in.s_addr;
	if (h>>24 < 128) return h >> 24;
	if (h>>24 < 192) return h >> 16;
	return h >> 8;
}