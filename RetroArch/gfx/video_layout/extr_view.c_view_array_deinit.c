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
struct TYPE_3__ {int views_count; int /*<<< orphan*/ * views; } ;
typedef  TYPE_1__ view_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_deinit (int /*<<< orphan*/ *) ; 

void view_array_deinit(view_array_t *view_array)
{
   int i;

   for (i = 0; i < view_array->views_count; ++i)
      view_deinit(&view_array->views[i]);
   free(view_array->views);
   view_array->views = NULL;
   view_array->views_count = 0;
}