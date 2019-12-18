#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;

/* Type definitions */
struct TYPE_21__ {int layers_count; int /*<<< orphan*/  bounds; TYPE_4__* layers; } ;
typedef  TYPE_2__ view_t ;
typedef  int /*<<< orphan*/  video_layout_orientation_t ;
typedef  int /*<<< orphan*/  video_layout_color_t ;
struct TYPE_22__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ video_layout_bounds_t ;
typedef  int /*<<< orphan*/  scope_t ;
struct TYPE_23__ {int elements_count; int /*<<< orphan*/ * elements; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ layer_t ;
struct TYPE_19__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_24__ {int components_count; TYPE_16__ bounds; TYPE_1__* components; } ;
typedef  TYPE_5__ element_t ;
struct TYPE_20__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int /*<<< orphan*/  bounds_scale (TYPE_16__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bounds_union (int /*<<< orphan*/ *,TYPE_16__*) ; 
 int bounds_valid (TYPE_3__*) ; 
 int /*<<< orphan*/  color_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  element_apply_orientation (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  element_copy (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* layer_add_element (TYPE_4__*) ; 
 TYPE_4__* view_emplace_layer (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void merge_group(scope_t *scope, view_t *view, view_t *group,
   bool has_bounds, video_layout_bounds_t n_bounds, video_layout_orientation_t n_orient, video_layout_color_t n_color)
{
   int i, j, k;
   bool constrain = bounds_valid(&n_bounds);

   for (i = 0; i < group->layers_count; ++i)
   {
      layer_t *group_layer;
      layer_t *layer;

      group_layer = &group->layers[i];
      layer = view_emplace_layer(view, group_layer->name);

      for (j = 0; j < group_layer->elements_count; ++j)
      {
         element_t *elem;
         elem = layer_add_element(layer);

         element_copy(elem, &group_layer->elements[j]);

         for (k = 0; k < elem->components_count; ++k)
            color_mod(&elem->components->color, &n_color);

         if (n_orient)
            element_apply_orientation(elem, n_orient);

         if (constrain)
         {
            bounds_scale(&elem->bounds, &n_bounds);
            elem->bounds.x += n_bounds.x;
            elem->bounds.y += n_bounds.y;
         }

         if (!has_bounds)
            view->bounds = bounds_union(&view->bounds, &elem->bounds);
      }
   }
}