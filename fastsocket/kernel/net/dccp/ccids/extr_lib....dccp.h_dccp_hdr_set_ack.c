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
struct dccp_hdr_ack_bits {int /*<<< orphan*/  dccph_ack_nr_low; int /*<<< orphan*/  dccph_ack_nr_high; scalar_t__ dccph_reserved1; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int const) ; 
 int /*<<< orphan*/  htons (int const) ; 

__attribute__((used)) static inline void dccp_hdr_set_ack(struct dccp_hdr_ack_bits *dhack,
				    const u64 gsr)
{
	dhack->dccph_reserved1 = 0;
	dhack->dccph_ack_nr_high = htons(gsr >> 32);
	dhack->dccph_ack_nr_low  = htonl(gsr & 0xffffffff);
}