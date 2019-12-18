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
typedef  int /*<<< orphan*/  view_array_t ;
typedef  int /*<<< orphan*/  scope_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ rxml_node_t ;
typedef  int /*<<< orphan*/  rxml_document_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  init_device_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_screen_params (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  load_top_level (int /*<<< orphan*/ *,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  load_views (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rxml_node_attrib (TYPE_1__*,char*) ; 
 TYPE_1__* rxml_root_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  view_array_init (int /*<<< orphan*/ *,int) ; 

bool load(view_array_t *view_array, rxml_document_t *doc)
{
   bool result;
   scope_t scope;
   int view_count;
   rxml_node_t *root = rxml_root_node(doc);

   if (strcmp(root->name, "mamelayout") ||
         strcmp(rxml_node_attrib(root, "version"), "2"))
   {
      RARCH_LOG("video_layout: invalid MAME Layout file\n");
      return false;
   }

   result = false;

   scope_init(&scope);
   init_device_params(&scope);
   init_screen_params(&scope, 0);
   init_screen_params(&scope, 1);

   if (!load_top_level(&scope, &view_count, root))
      result = false;

   view_array_init(view_array, view_count);

   if (!load_views(&scope, view_array, root))
      result = false;

   scope_deinit(&scope);

   return result;
}