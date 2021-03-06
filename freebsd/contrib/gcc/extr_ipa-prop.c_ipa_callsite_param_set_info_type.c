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
typedef  int /*<<< orphan*/  tree ;
struct cgraph_edge {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {TYPE_1__ info_type; } ;

/* Variables and functions */
 TYPE_2__* ipa_callsite_param (struct cgraph_edge*,int) ; 

__attribute__((used)) static inline void
ipa_callsite_param_set_info_type (struct cgraph_edge *cs, int i, tree info_type1)
{
  ipa_callsite_param (cs, i)->info_type.value = info_type1;
}