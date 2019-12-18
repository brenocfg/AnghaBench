#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  view_t ;
struct TYPE_6__ {int /*<<< orphan*/ * views; } ;
typedef  TYPE_1__ view_array_t ;
typedef  int /*<<< orphan*/  scope_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; struct TYPE_7__* next; struct TYPE_7__* children; } ;
typedef  TYPE_2__ rxml_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  load_view (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  scope_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_push (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  view_count_screens (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_normalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_sort_layers (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load_views(scope_t *scope, view_array_t *view_array, rxml_node_t *root)
{
   rxml_node_t *node;
   bool result = true;
   int i = 0;

   for (node = root->children; node; node = node->next)
   {
      if (strcmp(node->name, "view") == 0)
      {
         view_t *view;
         view = &view_array->views[i];

         scope_push(scope);

         if (!load_view(scope, view, node, true))
            result = false;

         view_sort_layers(view);
         view_normalize(view);
         view_count_screens(view);

         scope_pop(scope);

         ++i;
      }
   }

   return result;
}