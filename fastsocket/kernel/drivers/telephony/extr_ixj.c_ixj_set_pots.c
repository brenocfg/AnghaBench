#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pots_pstn; } ;
struct TYPE_6__ {int rly1; } ;
struct TYPE_7__ {int /*<<< orphan*/  byte; TYPE_1__ bits; } ;
struct TYPE_9__ {scalar_t__ cardtype; scalar_t__ port; TYPE_3__ flags; scalar_t__ XILINXbase; TYPE_2__ pld_slicw; } ;
typedef  TYPE_4__ IXJ ;

/* Variables and functions */
 scalar_t__ PORT_PSTN ; 
 scalar_t__ QTI_LINEJACK ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ixj_set_pots(IXJ *j, int arg)
{
	if (j->cardtype == QTI_LINEJACK) {
		if (arg) {
			if (j->port == PORT_PSTN) {
				j->pld_slicw.bits.rly1 = 0;
				outb(j->pld_slicw.byte, j->XILINXbase + 0x01);
				j->flags.pots_pstn = 1;
				return 1;
			} else {
				j->flags.pots_pstn = 0;
				return 0;
			}
		} else {
			j->pld_slicw.bits.rly1 = 1;
			outb(j->pld_slicw.byte, j->XILINXbase + 0x01);
			j->flags.pots_pstn = 0;
			return 1;
		}
	} else {
		return 0;
	}
}