#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  dts_name; int /*<<< orphan*/  dts_object; } ;
typedef  TYPE_2__ dtrace_syminfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_11__ {scalar_t__ dn_kind; TYPE_1__* dn_ident; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pcb_hdl; } ;
struct TYPE_12__ {size_t st_size; } ;
struct TYPE_9__ {TYPE_2__* di_data; } ;
typedef  TYPE_4__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ DT_NODE_SYM ; 
 size_t dt_node_type_size (TYPE_3__ const*) ; 
 int dtrace_lookup_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* yypcb ; 

size_t
dt_node_sizeof(const dt_node_t *dnp)
{
	dtrace_syminfo_t *sip;
	GElf_Sym sym;
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;

	/*
	 * The size of the node as used for the sizeof() operator depends on
	 * the kind of the node.  If the node is a SYM, the size is obtained
	 * from the symbol table; if it is not a SYM, the size is determined
	 * from the node's type.  This is slightly different from C's sizeof()
	 * operator in that (for example) when applied to a function, sizeof()
	 * will evaluate to the length of the function rather than the size of
	 * the function type.
	 */
	if (dnp->dn_kind != DT_NODE_SYM)
		return (dt_node_type_size(dnp));

	sip = dnp->dn_ident->di_data;

	if (dtrace_lookup_by_name(dtp, sip->dts_object,
	    sip->dts_name, &sym, NULL) == -1)
		return (0);

	return (sym.st_size);
}