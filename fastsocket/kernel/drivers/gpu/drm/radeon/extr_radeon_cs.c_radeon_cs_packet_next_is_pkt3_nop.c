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
struct radeon_cs_parser {int /*<<< orphan*/  idx; } ;
struct radeon_cs_packet {scalar_t__ type; scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ RADEON_PACKET3_NOP ; 
 scalar_t__ RADEON_PACKET_TYPE3 ; 
 int radeon_cs_packet_parse (struct radeon_cs_parser*,struct radeon_cs_packet*,int /*<<< orphan*/ ) ; 

bool radeon_cs_packet_next_is_pkt3_nop(struct radeon_cs_parser *p)
{
	struct radeon_cs_packet p3reloc;
	int r;

	r = radeon_cs_packet_parse(p, &p3reloc, p->idx);
	if (r)
		return false;
	if (p3reloc.type != RADEON_PACKET_TYPE3)
		return false;
	if (p3reloc.opcode != RADEON_PACKET3_NOP)
		return false;
	return true;
}