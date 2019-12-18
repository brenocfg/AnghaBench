#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enable; struct TYPE_4__* list; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ image_transform ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ image_transform_end ; 
 TYPE_1__* image_transform_first ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
transform_enable(const char *name)
{
   /* Everything starts out enabled, so if we see an 'enable' disabled
    * everything else the first time round.
    */
   static int all_disabled = 0;
   int found_it = 0;
   image_transform *list = image_transform_first;

   while (list != &image_transform_end)
   {
      if (strcmp(list->name, name) == 0)
      {
         list->enable = 1;
         found_it = 1;
      }
      else if (!all_disabled)
         list->enable = 0;

      list = list->list;
   }

   all_disabled = 1;

   if (!found_it)
   {
      fprintf(stderr, "pngvalid: --transform-enable=%s: unknown transform\n",
         name);
      exit(99);
   }
}