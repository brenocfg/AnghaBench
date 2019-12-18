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
struct TYPE_3__ {struct TYPE_3__* next; struct TYPE_3__* children; } ;
typedef  TYPE_1__ rxml_node_t ;

/* Variables and functions */

__attribute__((used)) static int child_count(rxml_node_t *node)
{
   rxml_node_t *child;
   int res = 0;

   for (child = node->children; child; child = child->next)
      ++res;

   return res;
}