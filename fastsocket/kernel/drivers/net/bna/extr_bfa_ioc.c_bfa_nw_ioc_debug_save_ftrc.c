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
struct bfa_ioc {int dbg_fwsave_len; int /*<<< orphan*/  dbg_fwsave; scalar_t__ dbg_fwsave_once; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_nw_ioc_debug_fwtrc (struct bfa_ioc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
bfa_nw_ioc_debug_save_ftrc(struct bfa_ioc *ioc)
{
	int tlen;

	if (ioc->dbg_fwsave_once) {
		ioc->dbg_fwsave_once = 0;
		if (ioc->dbg_fwsave_len) {
			tlen = ioc->dbg_fwsave_len;
			bfa_nw_ioc_debug_fwtrc(ioc, ioc->dbg_fwsave, &tlen);
		}
	}
}