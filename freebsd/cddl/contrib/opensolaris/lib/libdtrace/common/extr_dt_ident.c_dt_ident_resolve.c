#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dn_kind; TYPE_3__* dn_ident; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_8__ {TYPE_1__* din_root; } ;
typedef  TYPE_2__ dt_idnode_t ;
struct TYPE_9__ {int di_flags; scalar_t__ di_iarg; } ;
typedef  TYPE_3__ dt_ident_t ;

/* Variables and functions */
 int DT_IDFLG_INLINE ; 
#define  DT_NODE_AGG 133 
#define  DT_NODE_FUNC 132 
#define  DT_NODE_INLINE 131 
#define  DT_NODE_PROBE 130 
#define  DT_NODE_SYM 129 
#define  DT_NODE_VAR 128 
 scalar_t__ dt_node_is_dynamic (TYPE_1__ const*) ; 

dt_ident_t *
dt_ident_resolve(dt_ident_t *idp)
{
	while (idp->di_flags & DT_IDFLG_INLINE) {
		const dt_node_t *dnp = ((dt_idnode_t *)idp->di_iarg)->din_root;

		if (dnp == NULL)
			break; /* can't resolve any further yet */

		switch (dnp->dn_kind) {
		case DT_NODE_VAR:
		case DT_NODE_SYM:
		case DT_NODE_FUNC:
		case DT_NODE_AGG:
		case DT_NODE_INLINE:
		case DT_NODE_PROBE:
			idp = dnp->dn_ident;
			continue;
		}

		if (dt_node_is_dynamic(dnp))
			idp = dnp->dn_ident;
		else
			break;
	}

	return (idp);
}