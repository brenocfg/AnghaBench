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
typedef  int /*<<< orphan*/  u16 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  broadsheet_get_data (struct broadsheetfb_par*) ; 
 int /*<<< orphan*/  broadsheet_send_command (struct broadsheetfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static u16 broadsheet_read_reg(struct broadsheetfb_par *par, u16 reg)
{
	broadsheet_send_command(par, reg);
	msleep(100);
	return broadsheet_get_data(par);
}