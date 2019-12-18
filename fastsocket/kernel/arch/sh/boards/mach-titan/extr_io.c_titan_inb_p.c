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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ PXSEG (unsigned long) ; 
 int /*<<< orphan*/  ctrl_delay () ; 
 int ctrl_inb (unsigned long) ; 
 int ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port2adr (unsigned long) ; 

u8 titan_inb_p(unsigned long port)
{
        u8 v;

        if (PXSEG(port))
                v = ctrl_inb(port);
        else
                v = ctrl_inw(port2adr(port)) & 0xff;
        ctrl_delay();
        return v;
}