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
struct sk_buff {int dummy; } ;
struct isac {unsigned char (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;int rcvidx; int /*<<< orphan*/  rcvbuf; int /*<<< orphan*/  (* write_isac ) (struct isac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  DBG_RPACKET ; 
 int /*<<< orphan*/  DBG_SKB (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  DBG_WARN ; 
 int /*<<< orphan*/  D_L1L2 (struct isac*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int INDICATION ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_CMDR_RMC ; 
 int /*<<< orphan*/  ISAC_RBCL ; 
 int /*<<< orphan*/  ISAC_RSTA ; 
 unsigned char ISAC_RSTA_CRC ; 
 unsigned char ISAC_RSTA_RAB ; 
 unsigned char ISAC_RSTA_RDO ; 
 int PH_DATA ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isac_empty_fifo (struct isac*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isac_rme_interrupt(struct isac *isac)
{
	unsigned char val;
	int count;
	struct sk_buff *skb;
	
	val = isac->read_isac(isac, ISAC_RSTA);
	if ((val & (ISAC_RSTA_RDO | ISAC_RSTA_CRC | ISAC_RSTA_RAB) )
	     != ISAC_RSTA_CRC) {
		DBG(DBG_WARN, "RSTA %#x, dropped", val);
		isac->write_isac(isac, ISAC_CMDR, ISAC_CMDR_RMC);
		goto out;
	}

	count = isac->read_isac(isac, ISAC_RBCL) & 0x1f;
	DBG(DBG_IRQ, "RBCL %#x", count);
	if (count == 0)
		count = 0x20;

	isac_empty_fifo(isac, count);
	count = isac->rcvidx;
	if (count < 1) {
		DBG(DBG_WARN, "count %d < 1", count);
		goto out;
	}

	skb = alloc_skb(count, GFP_ATOMIC);
	if (!skb) {
		DBG(DBG_WARN, "no memory, dropping\n");
		goto out;
	}
	memcpy(skb_put(skb, count), isac->rcvbuf, count);
	DBG_SKB(DBG_RPACKET, skb);
	D_L1L2(isac, PH_DATA | INDICATION, skb);
 out:
	isac->rcvidx = 0;
}