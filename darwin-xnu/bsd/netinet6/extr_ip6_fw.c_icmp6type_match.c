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
struct ip6_fw {int fw_flg; unsigned int* fw_icmp6types; } ;
struct icmp6_hdr {int icmp6_type; } ;

/* Variables and functions */
 int IPV6_FW_F_ICMPBIT ; 
 int IPV6_FW_ICMPTYPES_DIM ; 

__attribute__((used)) static int
icmp6type_match(struct icmp6_hdr *icmp6, struct ip6_fw *f)
{
	int type;

	if (!(f->fw_flg & IPV6_FW_F_ICMPBIT))
		return(1);

	type = icmp6->icmp6_type;

	/* check for matching type in the bitmap */
	if (type < IPV6_FW_ICMPTYPES_DIM * sizeof(unsigned) * 8 &&
		(f->fw_icmp6types[type / (sizeof(unsigned) * 8)] &
		(1U << (type % (8 * sizeof(unsigned))))))
		return(1);

	return(0); /* no match */
}