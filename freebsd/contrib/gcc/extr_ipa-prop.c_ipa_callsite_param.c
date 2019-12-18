#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipa_jump_func {int dummy; } ;
struct cgraph_edge {int dummy; } ;
struct TYPE_2__ {struct ipa_jump_func* ipa_param_map; } ;

/* Variables and functions */
 TYPE_1__* IPA_EDGE_REF (struct cgraph_edge*) ; 

struct ipa_jump_func *
ipa_callsite_param (struct cgraph_edge *cs, int i)
{
  return &(IPA_EDGE_REF (cs)->ipa_param_map[i]);
}