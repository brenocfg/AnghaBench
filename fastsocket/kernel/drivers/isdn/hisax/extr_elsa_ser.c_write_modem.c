#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int transcnt; int transp; int IER; scalar_t__ transbuf; } ;
struct TYPE_6__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;
struct BCState {TYPE_3__* tx_skb; struct IsdnCardState* cs; } ;
struct TYPE_7__ {int len; } ;

/* Variables and functions */
 int MAX_MODEM_BUF ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  serial_outp (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_pull (TYPE_3__*,int) ; 

__attribute__((used)) static inline int
write_modem(struct BCState *bcs) {
	int ret=0;
	struct IsdnCardState *cs = bcs->cs;
	int count, len, fp;
	
	if (!bcs->tx_skb)
		return 0;
	if (bcs->tx_skb->len <= 0)
		return 0;
	len = bcs->tx_skb->len;
	if (len > MAX_MODEM_BUF - cs->hw.elsa.transcnt)
		len = MAX_MODEM_BUF - cs->hw.elsa.transcnt;
	fp = cs->hw.elsa.transcnt + cs->hw.elsa.transp;
	fp &= (MAX_MODEM_BUF -1);
	count = len;
	if (count > MAX_MODEM_BUF - fp) {
		count = MAX_MODEM_BUF - fp;
		skb_copy_from_linear_data(bcs->tx_skb,
					  cs->hw.elsa.transbuf + fp, count);
		skb_pull(bcs->tx_skb, count);
		cs->hw.elsa.transcnt += count;
		ret = count;
		count = len - count;
		fp = 0;
	}
	skb_copy_from_linear_data(bcs->tx_skb,
				  cs->hw.elsa.transbuf + fp, count);
	skb_pull(bcs->tx_skb, count);
	cs->hw.elsa.transcnt += count;
	ret += count;
	
	if (cs->hw.elsa.transcnt && 
	    !(cs->hw.elsa.IER & UART_IER_THRI)) {
			cs->hw.elsa.IER |= UART_IER_THRI;
		serial_outp(cs, UART_IER, cs->hw.elsa.IER);
	}
	return(ret);
}