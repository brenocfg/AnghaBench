#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int DT_NF_COOKED ; 
 int DT_NF_LVALUE ; 
 int /*<<< orphan*/  assert (int) ; 

void
dt_node_type_propagate(const dt_node_t *src, dt_node_t *dst)
{
	assert(src->dn_flags & DT_NF_COOKED);
	dst->dn_flags = src->dn_flags & ~DT_NF_LVALUE;
	dst->dn_ctfp = src->dn_ctfp;
	dst->dn_type = src->dn_type;
}