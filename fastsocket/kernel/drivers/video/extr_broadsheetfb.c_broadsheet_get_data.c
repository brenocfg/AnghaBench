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
typedef  int /*<<< orphan*/  u16 ;
struct broadsheetfb_par {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_ctl ) (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* get_hdb ) (struct broadsheetfb_par*) ;int /*<<< orphan*/  (* wait_for_rdy ) (struct broadsheetfb_par*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BS_CS ; 
 int /*<<< orphan*/  BS_DC ; 
 int /*<<< orphan*/  BS_WR ; 
 int /*<<< orphan*/  stub1 (struct broadsheetfb_par*) ; 
 int /*<<< orphan*/  stub2 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct broadsheetfb_par*) ; 
 int /*<<< orphan*/  stub6 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 broadsheet_get_data(struct broadsheetfb_par *par)
{
	u16 res;
	/* wait for ready to go hi. (lo is busy) */
	par->board->wait_for_rdy(par);

	/* cs lo, dc lo for cmd, we lo for each data, db as usual */
	par->board->set_ctl(par, BS_DC, 1);
	par->board->set_ctl(par, BS_CS, 0);
	par->board->set_ctl(par, BS_WR, 0);

	res = par->board->get_hdb(par);

	/* strobe wr */
	par->board->set_ctl(par, BS_WR, 1);
	par->board->set_ctl(par, BS_CS, 1);

	return res;
}