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
typedef  scalar_t__ u_char ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct IsdnCardState {int debug; int /*<<< orphan*/  HW_Flags; scalar_t__* dlog; } ;

/* Variables and functions */
 int DEB_DLOG_HEX ; 
 int /*<<< orphan*/  FLG_LOCK_ATOMIC ; 
 int /*<<< orphan*/  HFCSX_SEL_B2_RX ; 
 int /*<<< orphan*/  HiSax_putstatus (struct IsdnCardState*,char*,char*,...) ; 
 int MAX_DLOG_SPACE ; 
 int /*<<< orphan*/  QuickHex (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* read_fifo (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
receive_emsg(struct IsdnCardState *cs)
{
	int count = 5;
	u_char *ptr;
	struct sk_buff *skb;

	if (test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
		debugl1(cs, "echo_rec_data blocked");
		return;
	}
	do {
	  skb = read_fifo(cs, HFCSX_SEL_B2_RX, 0);
	  if (skb) {
	    if (cs->debug & DEB_DLOG_HEX) {
	      ptr = cs->dlog;
	      if ((skb->len) < MAX_DLOG_SPACE / 3 - 10) {
		*ptr++ = 'E';
		*ptr++ = 'C';
		*ptr++ = 'H';
		*ptr++ = 'O';
		*ptr++ = ':';
		ptr += QuickHex(ptr, skb->data, skb->len);
		ptr--;
		*ptr++ = '\n';
		*ptr = 0;
		HiSax_putstatus(cs, NULL, cs->dlog);
	      } else
		HiSax_putstatus(cs, "LogEcho: ", "warning Frame too big (%d)", skb->len);
	    }
	    dev_kfree_skb_any(skb);
	  }
	} while (--count && skb);

	test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
	return;
}