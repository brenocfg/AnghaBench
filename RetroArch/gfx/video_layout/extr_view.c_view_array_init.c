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
typedef  int /*<<< orphan*/  view_t ;
struct TYPE_3__ {int views_count; int /*<<< orphan*/ * views; } ;
typedef  TYPE_1__ view_array_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 

void view_array_init(view_array_t *view_array, int views_count)
{
   view_array->views = (view_t*)(views_count > 0 ?
      calloc(views_count, sizeof(view_t)) : NULL);
   view_array->views_count = views_count;
}