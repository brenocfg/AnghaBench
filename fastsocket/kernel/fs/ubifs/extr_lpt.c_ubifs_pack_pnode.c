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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct ubifs_pnode {int num; TYPE_1__* lprops; } ;
struct ubifs_info {int pcnt_bits; int space_bits; int pnode_sz; scalar_t__ big_lpt; } ;
struct TYPE_2__ {int free; int dirty; int flags; } ;

/* Variables and functions */
 int LPROPS_INDEX ; 
 int UBIFS_LPT_CRC_BITS ; 
 int UBIFS_LPT_CRC_BYTES ; 
 int UBIFS_LPT_FANOUT ; 
 int UBIFS_LPT_PNODE ; 
 int UBIFS_LPT_TYPE_BITS ; 
 int crc16 (int,void*,int) ; 
 int /*<<< orphan*/  pack_bits (int /*<<< orphan*/ **,int*,int,int) ; 

void ubifs_pack_pnode(struct ubifs_info *c, void *buf,
		      struct ubifs_pnode *pnode)
{
	uint8_t *addr = buf + UBIFS_LPT_CRC_BYTES;
	int i, pos = 0;
	uint16_t crc;

	pack_bits(&addr, &pos, UBIFS_LPT_PNODE, UBIFS_LPT_TYPE_BITS);
	if (c->big_lpt)
		pack_bits(&addr, &pos, pnode->num, c->pcnt_bits);
	for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
		pack_bits(&addr, &pos, pnode->lprops[i].free >> 3,
			  c->space_bits);
		pack_bits(&addr, &pos, pnode->lprops[i].dirty >> 3,
			  c->space_bits);
		if (pnode->lprops[i].flags & LPROPS_INDEX)
			pack_bits(&addr, &pos, 1, 1);
		else
			pack_bits(&addr, &pos, 0, 1);
	}
	crc = crc16(-1, buf + UBIFS_LPT_CRC_BYTES,
		    c->pnode_sz - UBIFS_LPT_CRC_BYTES);
	addr = buf;
	pos = 0;
	pack_bits(&addr, &pos, crc, UBIFS_LPT_CRC_BITS);
}