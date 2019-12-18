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
struct net_device {scalar_t__ ml_priv; } ;
struct claw_privbk {int dummy; } ;
struct chbk {int /*<<< orphan*/  flag_a; scalar_t__ ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_BH_ACTIVE ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  unpack_read (struct net_device*) ; 

__attribute__((used)) static void
claw_irq_tasklet ( unsigned long data )
{
	struct chbk * p_ch;
        struct net_device  *dev;
        struct claw_privbk *       privptr;

	p_ch = (struct chbk *) data;
        dev = (struct net_device *)p_ch->ndev;
	CLAW_DBF_TEXT(4, trace, "IRQtask");
	privptr = (struct claw_privbk *)dev->ml_priv;
        unpack_read(dev);
        clear_bit(CLAW_BH_ACTIVE, (void *)&p_ch->flag_a);
	CLAW_DBF_TEXT(4, trace, "TskletXt");
        return;
}