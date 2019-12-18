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
typedef  int u32 ;
struct TYPE_2__ {int ctrl; } ;
struct hdlc_hw {TYPE_1__ ctrl; } ;
struct fritzcard {scalar_t__ addr; } ;

/* Variables and functions */
 int AVM_HDLC_1 ; 
 int AVM_HDLC_2 ; 
 scalar_t__ CHIP_INDEX ; 
 scalar_t__ CHIP_WINDOW ; 
 scalar_t__ HDLC_STATUS ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static inline void
__write_ctrl_pci(struct fritzcard *fc, struct hdlc_hw *hdlc, u32 channel) {
	u32 idx = channel == 2 ? AVM_HDLC_2 : AVM_HDLC_1;

	outl(idx, fc->addr + CHIP_INDEX);
	outl(hdlc->ctrl.ctrl, fc->addr + CHIP_WINDOW + HDLC_STATUS);
}