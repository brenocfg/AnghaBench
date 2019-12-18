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
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dn_match_addr(__le16 addr1, __le16 addr2)
{
	__u16 tmp = le16_to_cpu(addr1) ^ le16_to_cpu(addr2);
	int match = 16;
	while(tmp) {
		tmp >>= 1;
		match--;
	}
	return match;
}