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
struct TYPE_4__ {int /*<<< orphan*/  display_name; } ;
typedef  TYPE_1__ core_info_t ;

/* Variables and functions */
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int core_info_qsort_func_display_name(const core_info_t *a,
      const core_info_t *b)
{
   if (!a || !b)
      return 0;

   if (string_is_empty(a->display_name) || string_is_empty(b->display_name))
      return 0;

   return strcasecmp(a->display_name, b->display_name);
}