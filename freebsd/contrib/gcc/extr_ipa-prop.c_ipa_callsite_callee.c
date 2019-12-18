#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cgraph_node {int dummy; } ;
struct cgraph_edge {struct cgraph_node* callee; } ;

/* Variables and functions */

struct cgraph_node *
ipa_callsite_callee (struct cgraph_edge *cs)
{
  return cs->callee;
}