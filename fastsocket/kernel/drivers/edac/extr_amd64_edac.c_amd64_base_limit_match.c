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
typedef  int u64 ;
struct amd64_pvt {int dummy; } ;

/* Variables and functions */
 int get_dram_base (struct amd64_pvt*,unsigned int) ; 
 int get_dram_limit (struct amd64_pvt*,unsigned int) ; 

__attribute__((used)) static bool amd64_base_limit_match(struct amd64_pvt *pvt, u64 sys_addr,
				   unsigned nid)
{
	u64 addr;

	/* The K8 treats this as a 40-bit value.  However, bits 63-40 will be
	 * all ones if the most significant implemented address bit is 1.
	 * Here we discard bits 63-40.  See section 3.4.2 of AMD publication
	 * 24592: AMD x86-64 Architecture Programmer's Manual Volume 1
	 * Application Programming.
	 */
	addr = sys_addr & 0x000000ffffffffffull;

	return ((addr >= get_dram_base(pvt, nid)) &&
		(addr <= get_dram_limit(pvt, nid)));
}