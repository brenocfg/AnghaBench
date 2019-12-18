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
typedef  int /*<<< orphan*/  ipa_methodlist_p ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct cgraph_node* ipa_methodlist_method (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipa_methodlist_next_method (int /*<<< orphan*/ ) ; 

struct cgraph_node *
ipa_remove_method (ipa_methodlist_p * wl)
{
  ipa_methodlist_p first;
  struct cgraph_node *return_method;

  first = *wl;
  *wl = ipa_methodlist_next_method (*wl);
  return_method = ipa_methodlist_method (first);
  free (first);
  return return_method;
}