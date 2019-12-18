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
typedef  int __be32 ;

/* Variables and functions */
 int htonl (int) ; 

__attribute__((used)) static __inline__ __be32 addr_bit_set(void *token, int fn_bit)
{
	__be32 *addr = token;

	return htonl(1 << ((~fn_bit)&0x1F)) & addr[fn_bit>>5];
}