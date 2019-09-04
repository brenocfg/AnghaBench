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
struct ip6_hdr {int dummy; } ;
struct icmp6_hdr {int icmp6_type; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ICMP6_ECHO_REQUEST ; 
 int ICMP6_FQDN_QUERY ; 
 int ICMP6_MEMBERSHIP_QUERY ; 
 int ICMP6_NI_QUERY ; 
 int ICMP6_WRUREQUEST ; 

__attribute__((used)) static int
is_icmp6_query(struct ip6_hdr *ip6, int off)
{
	const struct icmp6_hdr *icmp6;
	int icmp6_type;

	icmp6 = (struct icmp6_hdr *)((caddr_t)ip6 + off);
	icmp6_type = icmp6->icmp6_type;

	if (icmp6_type == ICMP6_ECHO_REQUEST ||
	    icmp6_type == ICMP6_MEMBERSHIP_QUERY ||
	    icmp6_type == ICMP6_WRUREQUEST ||
	    icmp6_type == ICMP6_FQDN_QUERY ||
	    icmp6_type == ICMP6_NI_QUERY)
		return(1);

	return(0);
}