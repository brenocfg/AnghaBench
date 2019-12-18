#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ PXSEG (unsigned long) ; 
 int /*<<< orphan*/  ctrl_outb (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ctrl_outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port2adr (unsigned long) ; 

void titan_outb(u8 value, unsigned long port)
{
        if (PXSEG(port))
                ctrl_outb(value, port);
        else
                ctrl_outw(value, port2adr(port));
}