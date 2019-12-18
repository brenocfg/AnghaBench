#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int rxg; scalar_t__ lom; scalar_t__ hom; } ;
struct TYPE_13__ {TYPE_4__ bits; int /*<<< orphan*/  byte; } ;
struct TYPE_10__ {int addr; scalar_t__ dev; scalar_t__ rw; } ;
struct TYPE_11__ {int /*<<< orphan*/  byte; TYPE_2__ bits; } ;
struct TYPE_9__ {scalar_t__ pcmciascp; } ;
struct TYPE_14__ {scalar_t__ cardtype; TYPE_5__ siadc; scalar_t__ XILINXbase; TYPE_3__ psccr; TYPE_1__ flags; } ;
typedef  TYPE_6__ IXJ ;

/* Variables and functions */
 scalar_t__ QTI_PHONECARD ; 
 int /*<<< orphan*/  ixj_PCcontrol_wait (TYPE_6__*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ixj_siadc(IXJ *j, int val)
{
	if(j->cardtype == QTI_PHONECARD){
		if(j->flags.pcmciascp){
			if(val == -1)
				return j->siadc.bits.rxg;

			if(val < 0 || val > 0x1F)
				return -1;

			j->siadc.bits.hom = 0;				/* Handset Out Mute */
			j->siadc.bits.lom = 0;				/* Line Out Mute */
			j->siadc.bits.rxg = val;			/*(0xC000 - 0x41C8) / 0x4EF;    RX PGA Gain */
			j->psccr.bits.addr = 6;				/* R/W Smart Cable Register Address */
			j->psccr.bits.rw = 0;				/* Read / Write flag */
			j->psccr.bits.dev = 0;
			outb(j->siadc.byte, j->XILINXbase + 0x00);
			outb(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);
			return j->siadc.bits.rxg;
		}
	}
	return -1;
}