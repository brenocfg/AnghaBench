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
struct TYPE_5__ {int led1; int led2; int led3; int led4; } ;
struct TYPE_6__ {int /*<<< orphan*/  byte; TYPE_1__ bits; } ;
struct TYPE_7__ {scalar_t__ cardtype; int /*<<< orphan*/  XILINXbase; TYPE_2__ pld_scrw; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 scalar_t__ QTI_LINEJACK ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void LED_SetState(int state, IXJ *j)
{
	if (j->cardtype == QTI_LINEJACK) {
		j->pld_scrw.bits.led1 = state & 0x1 ? 1 : 0;
		j->pld_scrw.bits.led2 = state & 0x2 ? 1 : 0;
		j->pld_scrw.bits.led3 = state & 0x4 ? 1 : 0;
		j->pld_scrw.bits.led4 = state & 0x8 ? 1 : 0;

		outb(j->pld_scrw.byte, j->XILINXbase);
	}
}