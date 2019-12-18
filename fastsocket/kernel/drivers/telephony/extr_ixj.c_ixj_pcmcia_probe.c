#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long DSPbase; unsigned long XILINXbase; int /*<<< orphan*/  cardtype; scalar_t__ board; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  QTI_PHONECARD ; 
 TYPE_1__* ixj_alloc () ; 
 int /*<<< orphan*/  ixj_selfprobe (TYPE_1__*) ; 

IXJ *ixj_pcmcia_probe(unsigned long dsp, unsigned long xilinx)
{
	IXJ *j = ixj_alloc();

	j->board = 0;

	j->DSPbase = dsp;
	j->XILINXbase = xilinx;
	j->cardtype = QTI_PHONECARD;
	ixj_selfprobe(j);
	return j;
}