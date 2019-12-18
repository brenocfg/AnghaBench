#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int* s6_addr; } ;
struct sockaddr_in6 {int sin6_family; int sin6_port; int sin6_flowinfo; int sin6_scope_id; TYPE_1__ sin6_addr; } ;

/* Variables and functions */
 int SLEN (struct sockaddr_in6 const*) ; 
 int snprintf (char*,size_t,char*,int,int,int,int,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int) ; 

__attribute__((used)) static int
debug_in6(char *str, size_t len, const struct sockaddr_in6 *sin6)
{
	const uint8_t *s = sin6->sin6_addr.s6_addr;

	return snprintf(str, len, "sin6_len=%u, sin6_family=%u, sin6_port=%u, "
	    "sin6_flowinfo=%u, "
	    "sin6_addr=%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:"
	    "%02x:%02x:%02x:%02x:%02x:%02x, sin6_scope_id=%u",
	    SLEN(sin6), sin6->sin6_family, sin6->sin6_port,
	    sin6->sin6_flowinfo, s[0x0], s[0x1], s[0x2], s[0x3], s[0x4], s[0x5],
	    s[0x6], s[0x7], s[0x8], s[0x9], s[0xa], s[0xb], s[0xc], s[0xd],
	    s[0xe], s[0xf], sin6->sin6_scope_id);
}