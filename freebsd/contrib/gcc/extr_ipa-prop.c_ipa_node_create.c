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
struct ipa_node {int dummy; } ;
struct cgraph_node {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  xcalloc (int,int) ; 

void
ipa_node_create (struct cgraph_node *node)
{
  node->aux = xcalloc (1, sizeof (struct ipa_node));
}