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
typedef  int u_char ;
struct console {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASE_ADDR ; 
 size_t CyCAR ; 
 size_t CyCCR ; 
 unsigned char CyENB_XMTR ; 
 size_t CyIER ; 
 size_t CyLICR ; 
 unsigned char CyNOTRANS ; 
 size_t CyTDR ; 
 size_t CyTEOIR ; 
 unsigned char CyTxMpty ; 
 size_t PccSCCTICR ; 
 size_t PccTPIACKR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int* pcc2chip ; 

void serial167_console_write(struct console *co, const char *str,
			     unsigned count)
{
	volatile unsigned char *base_addr = (u_char *) BASE_ADDR;
	unsigned long flags;
	volatile u_char sink;
	u_char ier;
	int port;
	u_char do_lf = 0;
	int i = 0;

	local_irq_save(flags);

	/* Ensure transmitter is enabled! */

	port = 0;
	base_addr[CyCAR] = (u_char) port;
	while (base_addr[CyCCR])
		;
	base_addr[CyCCR] = CyENB_XMTR;

	ier = base_addr[CyIER];
	base_addr[CyIER] = CyTxMpty;

	while (1) {
		if (pcc2chip[PccSCCTICR] & 0x20) {
			/* We have a Tx int. Acknowledge it */
			sink = pcc2chip[PccTPIACKR];
			if ((base_addr[CyLICR] >> 2) == port) {
				if (i == count) {
					/* Last char of string is now output */
					base_addr[CyTEOIR] = CyNOTRANS;
					break;
				}
				if (do_lf) {
					base_addr[CyTDR] = '\n';
					str++;
					i++;
					do_lf = 0;
				} else if (*str == '\n') {
					base_addr[CyTDR] = '\r';
					do_lf = 1;
				} else {
					base_addr[CyTDR] = *str++;
					i++;
				}
				base_addr[CyTEOIR] = 0;
			} else
				base_addr[CyTEOIR] = CyNOTRANS;
		}
	}

	base_addr[CyIER] = ier;

	local_irq_restore(flags);
}