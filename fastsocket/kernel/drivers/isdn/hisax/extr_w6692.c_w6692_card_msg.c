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
struct TYPE_3__ {int /*<<< orphan*/  iobase; } ;
struct TYPE_4__ {TYPE_1__ w6692; } ;
struct IsdnCardState {int /*<<< orphan*/  (* writeW6692 ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
#define  CARD_INIT 131 
#define  CARD_RELEASE 130 
#define  CARD_RESET 129 
#define  CARD_TEST 128 
 int /*<<< orphan*/  W6692_USR ; 
 int /*<<< orphan*/  W_IMASK ; 
 int /*<<< orphan*/  W_XDATA ; 
 int /*<<< orphan*/  initW6692 (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resetW6692 (struct IsdnCardState*) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
w6692_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	switch (mt) {
		case CARD_RESET:
			resetW6692(cs);
			return (0);
		case CARD_RELEASE:
			cs->writeW6692(cs, W_IMASK, 0xff);
			release_region(cs->hw.w6692.iobase, 256);
			if (cs->subtyp == W6692_USR) {
				cs->writeW6692(cs, W_XDATA, 0x04);
			}
			return (0);
		case CARD_INIT:
			initW6692(cs, 3);
			return (0);
		case CARD_TEST:
			return (0);
	}
	return (0);
}