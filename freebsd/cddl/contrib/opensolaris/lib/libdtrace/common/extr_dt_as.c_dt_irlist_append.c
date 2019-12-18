#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ di_label; scalar_t__ di_instr; struct TYPE_5__* di_next; } ;
typedef  TYPE_1__ dt_irnode_t ;
struct TYPE_6__ {int /*<<< orphan*/  dl_len; TYPE_1__* dl_last; TYPE_1__* dl_list; } ;
typedef  TYPE_2__ dt_irlist_t ;

/* Variables and functions */
 scalar_t__ DIF_INSTR_NOP ; 
 scalar_t__ DT_LBL_NONE ; 

void
dt_irlist_append(dt_irlist_t *dlp, dt_irnode_t *dip)
{
	if (dlp->dl_last != NULL)
		dlp->dl_last->di_next = dip;
	else
		dlp->dl_list = dip;

	dlp->dl_last = dip;

	if (dip->di_label == DT_LBL_NONE || dip->di_instr != DIF_INSTR_NOP)
		dlp->dl_len++; /* don't count forward refs in instr count */
}