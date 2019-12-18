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
 int INDICATION ; 
 int /*<<< orphan*/  ISACSX_CMDRD ; 
 int /*<<< orphan*/  ISACSX_CMDRD_RMC ; 
 int /*<<< orphan*/  ISACSX_RBCLD ; 
 int /*<<< orphan*/  ISACSX_RSTAD ; 
 unsigned char ISACSX_RSTAD_CRC ; 
 unsigned char ISACSX_RSTAD_RAB ; 
 unsigned char ISACSX_RSTAD_RDO ; 
 unsigned char ISACSX_RSTAD_VFR ; 
 int PH_DATA ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  isac_empty_fifo (struct isac*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isacsx_rme_interrupt(struct isac *isac)
{
	int count;
	struct sk_buff *skb;
	unsigned char val;

	val = isac->read_isac(isac, ISACSX_RSTAD);
	if ((val & (ISACSX_RSTAD_VFR | 
		    ISACSX_RSTAD_RDO | 
		    ISACSX_RSTAD_CRC | 
		    ISACSX_RSTAD_RAB)) 
	    != (ISACSX_RSTAD_VFR | ISACSX_RSTAD_CRC)) {
		DBG(DBG_WARN, "RSTAD %#x, dropped", val);
		isac->write_isac(isac, ISACSX_CMDRD, ISACSX_CMDRD_RMC);
		goto out;
	}

	count = isac->read_isac(isac, ISACSX_RBCLD) & 0x1f;
	DBG(DBG_IRQ, "RBCLD %#x", count);
	if (count == 0)
		count = 0x20;

	isac_empty_fifo(isac, count);
	// strip trailing status byte
	count = isac->rcvidx - 1;
	if (count < 1) {
		DBG(DBG_WARN, "count %d < 1", count);
		goto out;
	}

	skb = dev_alloc_skb(count);
	if (!skb) {
		DBG(DBG_WARN, "no memory, dropping");
		goto out;
	}
	memcpy(skb_put(skb, count), isac->rcvbuf, count);
	DBG_SKB(DBG_RPACKET, skb);
	D_L1L2(isac, PH_DATA | INDICATION, skb);
 out:
	isac->rcvidx = 0;
}