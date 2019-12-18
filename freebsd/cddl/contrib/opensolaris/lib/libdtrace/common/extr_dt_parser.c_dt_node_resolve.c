#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_7__ {int dn_kind; int /*<<< orphan*/  dn_ident; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_8__ {scalar_t__ di_kind; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
#define  DT_NODE_AGG 133 
#define  DT_NODE_FUNC 132 
#define  DT_NODE_INLINE 131 
#define  DT_NODE_PROBE 130 
#define  DT_NODE_SYM 129 
#define  DT_NODE_VAR 128 
 TYPE_2__* dt_ident_resolve (int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_dynamic (TYPE_1__ const*) ; 

dt_ident_t *
dt_node_resolve(const dt_node_t *dnp, uint_t idkind)
{
	dt_ident_t *idp;

	switch (dnp->dn_kind) {
	case DT_NODE_VAR:
	case DT_NODE_SYM:
	case DT_NODE_FUNC:
	case DT_NODE_AGG:
	case DT_NODE_INLINE:
	case DT_NODE_PROBE:
		idp = dt_ident_resolve(dnp->dn_ident);
		return (idp->di_kind == idkind ? idp : NULL);
	}

	if (dt_node_is_dynamic(dnp)) {
		idp = dt_ident_resolve(dnp->dn_ident);
		return (idp->di_kind == idkind ? idp : NULL);
	}

	return (NULL);
}