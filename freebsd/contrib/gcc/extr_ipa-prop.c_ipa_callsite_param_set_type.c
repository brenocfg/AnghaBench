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
struct cgraph_edge {int dummy; } ;
typedef  enum jump_func_type { ____Placeholder_jump_func_type } jump_func_type ;
struct TYPE_4__ {TYPE_1__* ipa_param_map; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 TYPE_2__* IPA_EDGE_REF (struct cgraph_edge*) ; 

__attribute__((used)) static inline void
ipa_callsite_param_set_type (struct cgraph_edge *cs, int i,
			     enum jump_func_type type1)
{
  IPA_EDGE_REF (cs)->ipa_param_map[i].type = type1;
}