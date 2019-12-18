#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dn_ctfp; scalar_t__ dn_type; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_5__ {int /*<<< orphan*/  pcb_hdl; } ;

/* Variables and functions */
 scalar_t__ DT_STACK_CTFP (int /*<<< orphan*/ ) ; 
 scalar_t__ DT_STACK_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

int
dt_node_is_stack(const dt_node_t *dnp)
{
	return (dnp->dn_ctfp == DT_STACK_CTFP(yypcb->pcb_hdl) &&
	    dnp->dn_type == DT_STACK_TYPE(yypcb->pcb_hdl));
}