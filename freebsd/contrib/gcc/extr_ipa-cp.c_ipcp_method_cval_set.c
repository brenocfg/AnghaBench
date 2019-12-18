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
struct ipcp_formal {int /*<<< orphan*/  cval_type; } ;
struct cgraph_node {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ipcp_cval; } ;
struct TYPE_3__ {int /*<<< orphan*/  cval_type; } ;

/* Variables and functions */
 TYPE_2__* IPA_NODE_REF (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipcp_cval_get_cvalue (struct ipcp_formal*) ; 
 int /*<<< orphan*/  ipcp_cval_set_cvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_method_cval (struct cgraph_node*,int) ; 

__attribute__((used)) static inline void
ipcp_method_cval_set (struct cgraph_node *mt, int i, struct ipcp_formal *cval)
{
  IPA_NODE_REF (mt)->ipcp_cval[i].cval_type = cval->cval_type;
  ipcp_cval_set_cvalue (ipcp_method_cval (mt, i),
			ipcp_cval_get_cvalue (cval), cval->cval_type);
}