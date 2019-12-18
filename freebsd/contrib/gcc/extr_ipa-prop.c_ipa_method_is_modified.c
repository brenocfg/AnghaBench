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
struct cgraph_node {int dummy; } ;
struct TYPE_2__ {int* ipa_mod; } ;

/* Variables and functions */
 TYPE_1__* IPA_NODE_REF (struct cgraph_node*) ; 

__attribute__((used)) static inline bool
ipa_method_is_modified (struct cgraph_node *mt, int i)
{
  return IPA_NODE_REF (mt)->ipa_mod[i];
}