#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {long high; long low; } ;
struct TYPE_6__ {long* vol; } ;
struct TYPE_7__ {scalar_t__ XILINXbase; TYPE_1__ mix; } ;
typedef  TYPE_2__ IXJ ;
typedef  TYPE_3__ BYTES ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_Control (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_Enable_Mixer ; 
 int /*<<< orphan*/  SCI_End ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static int ixj_mixer(long val, IXJ *j)
{
	BYTES bytes;

	bytes.high = (val & 0x1F00) >> 8;
	bytes.low = val & 0x00FF;

        /* save mixer value so we can get back later on */
        j->mix.vol[bytes.high] = bytes.low;

	outb_p(bytes.high & 0x1F, j->XILINXbase + 0x03);	/* Load Mixer Address */

	outb_p(bytes.low, j->XILINXbase + 0x02);	/* Load Mixer Data */

	SCI_Control(j, SCI_Enable_Mixer);

	SCI_Control(j, SCI_End);

	return 0;
}