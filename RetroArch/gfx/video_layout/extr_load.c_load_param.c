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
typedef  int /*<<< orphan*/  scope_t ;
typedef  int /*<<< orphan*/  rxml_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 char* rxml_node_attrib (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  scope_eval (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  scope_generator (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  scope_param (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static bool load_param(scope_t *scope, rxml_node_t *node, bool can_repeat)
{
   const char *name;
   const char *value;
   const char *start;

   if (!(name = rxml_node_attrib(node, "name")))
   {
      RARCH_LOG("video_layout: <param> is missing 'name' attribute\n");
      return false;
   }

   value = rxml_node_attrib(node, "value");
   start = rxml_node_attrib(node, "start");

   if (can_repeat && start)
   {
      const char *inc = rxml_node_attrib(node, "increment");
      const char *ls  = rxml_node_attrib(node, "lshift");
      const char *rs  = rxml_node_attrib(node, "rshift");

      if (inc || ls || rs)
      {
         scope_generator(scope, name, start, inc, ls, rs);
      }
      else
      {
         RARCH_LOG("video_layout: invalid generator <param name=\"%s\" /> missing increment/shift\n",
            scope_eval(scope, name));
         return false;
      }
   }
   else if (name && value)
   {
      scope_param(scope, name, value);
   }
   else
   {
      RARCH_LOG("video_layout: invalid parameter <param name=\"%s\" /> missing value\n",
         scope_eval(scope, name));
      return false;
   }

   return true;
}