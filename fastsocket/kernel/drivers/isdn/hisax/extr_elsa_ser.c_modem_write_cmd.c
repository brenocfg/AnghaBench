#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int transcnt; int transp; int IER; scalar_t__ transbuf; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int MAX_MODEM_BUF ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serial_outp (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
modem_write_cmd(struct IsdnCardState *cs, u_char *buf, int len) {
	int count, fp;
	u_char *msg = buf;
	
	if (!len)
		return;
	if (len > (MAX_MODEM_BUF - cs->hw.elsa.transcnt)) {
		return;
	}
	fp = cs->hw.elsa.transcnt + cs->hw.elsa.transp;
	fp &= (MAX_MODEM_BUF -1);
	count = len;
	if (count > MAX_MODEM_BUF - fp) {
		count = MAX_MODEM_BUF - fp;
		memcpy(cs->hw.elsa.transbuf + fp, msg, count);
		cs->hw.elsa.transcnt += count;
		msg += count;
		count = len - count;
		fp = 0;
	}
	memcpy(cs->hw.elsa.transbuf + fp, msg, count);
	cs->hw.elsa.transcnt += count;
	if (cs->hw.elsa.transcnt && 
	    !(cs->hw.elsa.IER & UART_IER_THRI)) {
		cs->hw.elsa.IER |= UART_IER_THRI;
		serial_outp(cs, UART_IER, cs->hw.elsa.IER);
	}
}