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
struct cgraph_node {int dummy; } ;
typedef  TYPE_1__* ipa_methodlist_p ;
struct TYPE_3__ {struct cgraph_node* method_p; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cgraph_node *
ipa_methodlist_method (ipa_methodlist_p wl)
{
  return wl->method_p;
}