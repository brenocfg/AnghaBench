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
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;
struct hdlc_hw {TYPE_1__ ctrl; } ;
struct fritzcard {int type; int /*<<< orphan*/  name; struct hdlc_hw* hdlc; } ;
struct bchannel {int nr; struct fritzcard* hw; } ;

/* Variables and functions */
#define  AVM_FRITZ_PCI 129 
#define  AVM_FRITZ_PCIV2 128 
 int /*<<< orphan*/  __write_ctrl_pci (struct fritzcard*,struct hdlc_hw*,char) ; 
 int /*<<< orphan*/  __write_ctrl_pciv2 (struct fritzcard*,struct hdlc_hw*,char) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char,int,int /*<<< orphan*/ ) ; 

void
write_ctrl(struct bchannel *bch, int which) {
	struct fritzcard *fc = bch->hw;
	struct hdlc_hw *hdlc;

	hdlc = &fc->hdlc[(bch->nr - 1) & 1];
	pr_debug("%s: hdlc %c wr%x ctrl %x\n", fc->name, '@' + bch->nr,
		which, hdlc->ctrl.ctrl);
	switch (fc->type) {
	case AVM_FRITZ_PCIV2:
		__write_ctrl_pciv2(fc, hdlc, bch->nr);
		break;
	case AVM_FRITZ_PCI:
		__write_ctrl_pci(fc, hdlc, bch->nr);
		break;
	}
}