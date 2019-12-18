#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hecubafb_par {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_ctl ) (struct hecubafb_par*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCB_CD_BIT ; 
 int /*<<< orphan*/  apollo_send_data (struct hecubafb_par*,unsigned char) ; 
 int /*<<< orphan*/  stub1 (struct hecubafb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct hecubafb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void apollo_send_command(struct hecubafb_par *par, unsigned char data)
{
	/* command so set CD to high */
	par->board->set_ctl(par, HCB_CD_BIT, 1);

	/* actually strobe with command */
	apollo_send_data(par, data);

	/* clear CD back to low */
	par->board->set_ctl(par, HCB_CD_BIT, 0);
}