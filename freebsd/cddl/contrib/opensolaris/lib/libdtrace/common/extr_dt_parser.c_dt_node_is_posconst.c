#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ dn_kind; scalar_t__ dn_value; int dn_flags; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int DT_NF_SIGNED ; 
 scalar_t__ DT_NODE_INT ; 

int
dt_node_is_posconst(const dt_node_t *dnp)
{
	return (dnp->dn_kind == DT_NODE_INT && dnp->dn_value != 0 && (
	    (dnp->dn_flags & DT_NF_SIGNED) == 0 || (int64_t)dnp->dn_value > 0));
}