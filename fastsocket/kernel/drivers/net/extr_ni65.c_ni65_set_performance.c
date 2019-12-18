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
struct priv {size_t cardno; } ;
struct TYPE_2__ {int config; } ;

/* Variables and functions */
 short CSR0 ; 
 int CSR0_CLRALL ; 
 int CSR0_STOP ; 
 scalar_t__ L_ADDRREG ; 
 scalar_t__ L_BUSIF ; 
 scalar_t__ PORT ; 
 TYPE_1__* cards ; 
 int csr80 ; 
 int inw (scalar_t__) ; 
 scalar_t__ isa0 ; 
 scalar_t__ isa1 ; 
 int /*<<< orphan*/  outw (short,scalar_t__) ; 
 int /*<<< orphan*/  writereg (int,int) ; 

__attribute__((used)) static void ni65_set_performance(struct priv *p)
{
	writereg(CSR0_STOP | CSR0_CLRALL,CSR0); /* STOP */

	if( !(cards[p->cardno].config & 0x02) )
		return;

	outw(80,PORT+L_ADDRREG);
	if(inw(PORT+L_ADDRREG) != 80)
		return;

	writereg( (csr80 & 0x3fff) ,80); /* FIFO watermarks */
	outw(0,PORT+L_ADDRREG);
	outw((short)isa0,PORT+L_BUSIF); /* write ISA 0: DMA_R : isa0 * 50ns */
	outw(1,PORT+L_ADDRREG);
	outw((short)isa1,PORT+L_BUSIF); /* write ISA 1: DMA_W : isa1 * 50ns	*/

	outw(CSR0,PORT+L_ADDRREG);	/* switch back to CSR0 */
}