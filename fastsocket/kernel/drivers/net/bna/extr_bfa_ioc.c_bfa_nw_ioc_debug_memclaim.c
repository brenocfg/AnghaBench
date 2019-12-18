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
struct TYPE_2__ {scalar_t__ auto_recover; } ;
struct bfa_ioc {TYPE_1__ iocpf; int /*<<< orphan*/  dbg_fwsave_len; void* dbg_fwsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_DBG_FWTRC_LEN ; 

void
bfa_nw_ioc_debug_memclaim(struct bfa_ioc *ioc, void *dbg_fwsave)
{
	ioc->dbg_fwsave = dbg_fwsave;
	ioc->dbg_fwsave_len = ioc->iocpf.auto_recover ? BNA_DBG_FWTRC_LEN : 0;
}