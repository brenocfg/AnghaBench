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
struct TYPE_3__ {int layers_count; int /*<<< orphan*/ * name; int /*<<< orphan*/ * layers; int /*<<< orphan*/ * screens; } ;
typedef  TYPE_1__ view_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_deinit (int /*<<< orphan*/ *) ; 

void view_deinit(view_t *view)
{
   int i;

   free(view->screens);

   for (i = 0; i < view->layers_count; ++i)
      layer_deinit(&view->layers[i]);

   free(view->layers);
   free(view->name);
}