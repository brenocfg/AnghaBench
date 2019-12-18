#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cgraph_node {int dummy; } ;
typedef  enum cvalue_type { ____Placeholder_cvalue_type } cvalue_type ;
struct TYPE_4__ {TYPE_1__* ipcp_cval; } ;
struct TYPE_3__ {int cval_type; } ;

/* Variables and functions */
 TYPE_2__* IPA_NODE_REF (struct cgraph_node*) ; 

__attribute__((used)) static inline void
ipcp_method_cval_set_cvalue_type (struct cgraph_node *mt, int i,
				  enum cvalue_type cval_type1)
{
  IPA_NODE_REF (mt)->ipcp_cval[i].cval_type = cval_type1;
}