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
struct bfa_ioc_s {int /*<<< orphan*/  dbg_fwsave_len; void* dbg_fwsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DBG_FWTRC_LEN ; 

void
bfa_ioc_debug_memclaim(struct bfa_ioc_s *ioc, void *dbg_fwsave)
{
	ioc->dbg_fwsave	    = dbg_fwsave;
	ioc->dbg_fwsave_len = BFA_DBG_FWTRC_LEN;
}