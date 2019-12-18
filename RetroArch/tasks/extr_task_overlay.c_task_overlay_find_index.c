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
struct overlay {int /*<<< orphan*/  name; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static ssize_t task_overlay_find_index(const struct overlay *ol,
      const char *name, size_t size)
{
   size_t i;

   if (!ol)
      return -1;

   for (i = 0; i < size; i++)
   {
      if (string_is_equal(ol[i].name, name))
         return i;
   }

   return -1;
}