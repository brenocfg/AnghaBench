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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int NES_AEQE_Q2_DATA_ETHERNET ; 

__attribute__((used)) static u8 *locate_mpa(u8 *pkt, u32 aeq_info)
{
	if (aeq_info & NES_AEQE_Q2_DATA_ETHERNET) {
		/* skip over ethernet header */
		pkt += ETH_HLEN;

		/* Skip over IP and TCP headers */
		pkt += 4 * (pkt[0] & 0x0f);
		pkt += 4 * ((pkt[12] >> 4) & 0x0f);
	}
	return pkt;
}