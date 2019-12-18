#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int high; int low; } ;
struct TYPE_10__ {int reg; } ;
struct TYPE_11__ {TYPE_1__ cr5; } ;
struct TYPE_12__ {TYPE_2__ SOP; } ;
struct TYPE_13__ {TYPE_3__ SOP_REGS; } ;
struct TYPE_14__ {TYPE_4__ m_DAAShadowRegs; scalar_t__ XILINXbase; } ;
typedef  TYPE_5__ IXJ ;
typedef  TYPE_6__ BYTES ;

/* Variables and functions */
 int ALISDAA_ID_BYTE ; 
 int /*<<< orphan*/  SCI_Control (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_Enable_DAA ; 
 int /*<<< orphan*/  SCI_End ; 
 int /*<<< orphan*/  SCI_Prepare (TYPE_5__*) ; 
 void* inb_p (scalar_t__) ; 
 int ixjdebug ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 

__attribute__((used)) static char daa_get_version(IXJ *j)
{
	BYTES bytes;

	if (!SCI_Prepare(j))
		return 0;

	bytes.high = 0x35;
	bytes.low = 0x00;
	outb_p(bytes.high, j->XILINXbase + 0x03);
	outb_p(bytes.low, j->XILINXbase + 0x02);

	if (!SCI_Control(j, SCI_Enable_DAA))
		return 0;

	bytes.high = inb_p(j->XILINXbase + 0x03);
	bytes.low = inb_p(j->XILINXbase + 0x02);
	if (bytes.low != ALISDAA_ID_BYTE) {
		if (ixjdebug & 0x0001)
			printk("DAA Get Version Cannot read DAA ID Byte high = %d low = %d\n", bytes.high, bytes.low);
		return 0;
	}
	if (!SCI_Control(j, SCI_Enable_DAA))
		return 0;

	if (!SCI_Control(j, SCI_End))
		return 0;

	bytes.high = inb_p(j->XILINXbase + 0x03);
	bytes.low = inb_p(j->XILINXbase + 0x02);
	if (ixjdebug & 0x0002)
		printk("DAA CR5 Byte high = 0x%x low = 0x%x\n", bytes.high, bytes.low);
	j->m_DAAShadowRegs.SOP_REGS.SOP.cr5.reg = bytes.high;
	return bytes.high;
}