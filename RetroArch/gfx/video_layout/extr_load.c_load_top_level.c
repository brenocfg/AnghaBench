#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scope_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; struct TYPE_6__* next; struct TYPE_6__* children; } ;
typedef  TYPE_1__ rxml_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  load_element (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  load_group (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  load_param (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool load_top_level(scope_t *scope, int *view_count, rxml_node_t *root)
{
   rxml_node_t *node;
   bool result = true;
   *view_count = 0;

   for (node = root->children; node; node = node->next)
   {
      if (strcmp(node->name, "param") == 0)
      {
         if (!load_param(scope, node, false))
            result = false;
      }

      else if (strcmp(node->name, "element") == 0)
      {
         if (!load_element(scope, node))
            result = false;
      }

      else if (strcmp(node->name, "group") == 0)
      {
         if (!load_group(scope, node))
            result = false;
      }

      else if (strcmp(node->name, "view") == 0)
         ++(*view_count);
   }

   return result;
}