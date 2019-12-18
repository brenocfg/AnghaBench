#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_9__ {int fifo_en; scalar_t__ fifos; } ;
struct TYPE_10__ {TYPE_3__ hfcpci; } ;
struct IsdnCardState {TYPE_4__ hw; } ;
struct TYPE_12__ {size_t f1; size_t f2; TYPE_2__* za; } ;
struct TYPE_7__ {TYPE_6__ txbz_b1; TYPE_6__ txbz_b2; } ;
struct TYPE_11__ {TYPE_1__ b_chans; } ;
typedef  TYPE_5__ fifo_area ;
typedef  TYPE_6__ bzfifo_type ;
struct TYPE_8__ {scalar_t__ z1; scalar_t__ z2; } ;

/* Variables and functions */
 scalar_t__ B_FIFO_SIZE ; 
 scalar_t__ B_SUB_VAL ; 
 int HFCPCI_FIFOEN_B1TX ; 
 int HFCPCI_FIFOEN_B2TX ; 
 int /*<<< orphan*/  HFCPCI_FIFO_EN ; 
 size_t MAX_B_FRAMES ; 
 int /*<<< orphan*/  Write_hfc (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hfcpci_clear_fifo_tx(struct IsdnCardState *cs, int fifo)
{       u_char fifo_state;
        bzfifo_type *bzt;

	if (fifo) {
	        bzt = &((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.txbz_b2;
		fifo_state = cs->hw.hfcpci.fifo_en & HFCPCI_FIFOEN_B2TX;
	} else {
	        bzt = &((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.txbz_b1;
		fifo_state = cs->hw.hfcpci.fifo_en & HFCPCI_FIFOEN_B1TX;
	}
	if (fifo_state)
	        cs->hw.hfcpci.fifo_en ^= fifo_state;
	Write_hfc(cs, HFCPCI_FIFO_EN, cs->hw.hfcpci.fifo_en);
	bzt->za[MAX_B_FRAMES].z1 = B_FIFO_SIZE + B_SUB_VAL - 1;
	bzt->za[MAX_B_FRAMES].z2 = bzt->za[MAX_B_FRAMES].z1;
	bzt->f1 = MAX_B_FRAMES;
	bzt->f2 = bzt->f1;	/* init F pointers to remain constant */
	if (fifo_state)
	        cs->hw.hfcpci.fifo_en |= fifo_state;
	Write_hfc(cs, HFCPCI_FIFO_EN, cs->hw.hfcpci.fifo_en);
}