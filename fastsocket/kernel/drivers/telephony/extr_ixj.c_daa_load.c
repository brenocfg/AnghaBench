#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_6__ {scalar_t__ XILINXbase; } ;
typedef  TYPE_1__ IXJ ;
typedef  TYPE_2__ BYTES ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_Control (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_Enable_DAA ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int daa_load(BYTES * p_bytes, IXJ *j)
{
	outb_p(p_bytes->high, j->XILINXbase + 0x03);
	outb_p(p_bytes->low, j->XILINXbase + 0x02);
	if (!SCI_Control(j, SCI_Enable_DAA))
		return 0;
	else
		return 1;
}