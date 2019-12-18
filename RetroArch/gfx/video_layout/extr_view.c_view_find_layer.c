#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int layers_count; TYPE_2__* layers; } ;
typedef  TYPE_1__ view_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ layer_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

layer_t *view_find_layer(view_t *view, const char *name)
{
   int i;

   for (i = 0; i < view->layers_count; ++i)
   {
      if (strcmp(name, view->layers[i].name) == 0)
         return &view->layers[i];
   }

   return NULL;
}