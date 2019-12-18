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
struct TYPE_4__ {int layers_count; int /*<<< orphan*/ * layers; } ;
typedef  TYPE_1__ view_t ;
typedef  int /*<<< orphan*/  layer_t ;

/* Variables and functions */
 int /*<<< orphan*/  layer_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vec_size (void**,int,int) ; 
 int /*<<< orphan*/ * view_find_layer (TYPE_1__*,char const*) ; 

layer_t *view_emplace_layer(view_t *view, const char *name)
{
   layer_t *layer = view_find_layer(view, name);

   if (!layer)
   {
      vec_size((void**)&view->layers, sizeof(layer_t), ++view->layers_count);

      layer = &view->layers[view->layers_count - 1];
      layer_init(layer, name);
   }

   return layer;
}