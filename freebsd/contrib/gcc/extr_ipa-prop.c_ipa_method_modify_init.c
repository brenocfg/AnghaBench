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

/* Variables and functions */
 int ipa_method_formal_count (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipa_method_modify_create (struct cgraph_node*) ; 
 int /*<<< orphan*/  ipa_method_modify_set (struct cgraph_node*,int,int) ; 

__attribute__((used)) static void
ipa_method_modify_init (struct cgraph_node *mt)
{
  int i, count;

  ipa_method_modify_create (mt);
  count = ipa_method_formal_count (mt);
  for (i = 0; i < count; i++)
    ipa_method_modify_set (mt, i, false);
}