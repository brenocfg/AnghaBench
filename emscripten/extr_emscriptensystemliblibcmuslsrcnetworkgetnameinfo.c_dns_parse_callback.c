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

/* Variables and functions */
 int RR_PTR ; 
 scalar_t__ __dn_expand (void const*,unsigned char const*,void const*,void*,int) ; 

__attribute__((used)) static int dns_parse_callback(void *c, int rr, const void *data, int len, const void *packet)
{
	if (rr != RR_PTR) return 0;
	if (__dn_expand(packet, (const unsigned char *)packet + 512,
	    data, c, 256) <= 0)
		*(char *)c = 0;
	return 0;
	
}