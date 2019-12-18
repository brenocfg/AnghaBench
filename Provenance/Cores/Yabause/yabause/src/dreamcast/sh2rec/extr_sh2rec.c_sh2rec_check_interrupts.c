#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ I; } ;
struct TYPE_8__ {TYPE_1__ part; int /*<<< orphan*/  all; } ;
struct TYPE_9__ {int* R; scalar_t__ VBR; int /*<<< orphan*/  PC; TYPE_2__ SR; } ;
struct TYPE_11__ {int NumberOfInterrupts; scalar_t__ isSleeping; TYPE_4__* interrupts; TYPE_3__ regs; } ;
struct TYPE_10__ {scalar_t__ level; int vector; } ;
typedef  TYPE_5__ SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/  MappedMemoryReadLong (scalar_t__) ; 
 int /*<<< orphan*/  MappedMemoryWriteLong (int,int /*<<< orphan*/ ) ; 

void sh2rec_check_interrupts(SH2_struct *c) {
    if(c->NumberOfInterrupts != 0) {
        if(c->interrupts[c->NumberOfInterrupts-1].level > c->regs.SR.part.I) {
            c->regs.R[15] -= 4;
            MappedMemoryWriteLong(c->regs.R[15], c->regs.SR.all);
            c->regs.R[15] -= 4;
            MappedMemoryWriteLong(c->regs.R[15], c->regs.PC);
            c->regs.SR.part.I = c->interrupts[c->NumberOfInterrupts - 1].level;
            c->regs.PC = MappedMemoryReadLong(c->regs.VBR + (c->interrupts[c->NumberOfInterrupts-1].vector << 2));
            c->NumberOfInterrupts--;
            c->isSleeping = 0;
        }
    }
}