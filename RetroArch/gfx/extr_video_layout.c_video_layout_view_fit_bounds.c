#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {float w; float h; float x; float y; } ;
struct TYPE_21__ {int w; int h; } ;
struct TYPE_29__ {int layers_count; TYPE_8__* screens; TYPE_3__ render_bounds; TYPE_11__* layers; TYPE_1__ bounds; } ;
typedef  TYPE_9__ view_t ;
struct TYPE_16__ {int w; int h; } ;
typedef  TYPE_10__ video_layout_bounds_t ;
struct TYPE_17__ {int elements_count; TYPE_12__* elements; } ;
typedef  TYPE_11__ layer_t ;
struct TYPE_25__ {float x; float y; int w; int h; } ;
struct TYPE_22__ {int x; int y; int w; int h; } ;
struct TYPE_18__ {int components_count; TYPE_5__ render_bounds; TYPE_13__* components; TYPE_2__ bounds; } ;
typedef  TYPE_12__ element_t ;
struct TYPE_28__ {float x; float y; int w; int h; } ;
struct TYPE_26__ {size_t index; } ;
struct TYPE_27__ {TYPE_6__ screen; } ;
struct TYPE_24__ {int x; int y; int w; int h; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_8__ render_bounds; TYPE_7__ attr; TYPE_4__ bounds; } ;
typedef  TYPE_13__ component_t ;
struct TYPE_20__ {TYPE_9__* view; } ;

/* Variables and functions */
 float MIN (int,int) ; 
 scalar_t__ VIDEO_LAYOUT_C_SCREEN ; 
 TYPE_15__* video_layout_state ; 

void video_layout_view_fit_bounds(video_layout_bounds_t bounds)
{
   view_t *view;
   float c, dx, dy;
   int i, j, k;

   view = video_layout_state->view;

   c = MIN(bounds.w / view->bounds.w, bounds.h / view->bounds.h);

   dx = view->bounds.w * c;
   dy = view->bounds.h * c;

   view->render_bounds.w = dx;
   view->render_bounds.h = dy;
   view->render_bounds.x = (bounds.w - dx) / 2.f;
   view->render_bounds.y = (bounds.h - dy) / 2.f;

   for (i = 0; i < view->layers_count; ++i)
   {
      layer_t *layer;
      layer = &view->layers[i];

      for (j = 0; j < layer->elements_count; ++j)
      {
         element_t *elem;
         elem = &layer->elements[j];

         elem->render_bounds.x = elem->bounds.x * view->render_bounds.w + view->render_bounds.x;
         elem->render_bounds.y = elem->bounds.y * view->render_bounds.h + view->render_bounds.y;
         elem->render_bounds.w = elem->bounds.w * view->render_bounds.w;
         elem->render_bounds.h = elem->bounds.h * view->render_bounds.h;

         for (k = 0; k < elem->components_count; ++k)
         {
            component_t *comp;
            comp = &elem->components[k];

            comp->render_bounds.x = comp->bounds.x * elem->render_bounds.w + elem->render_bounds.x;
            comp->render_bounds.y = comp->bounds.y * elem->render_bounds.h + elem->render_bounds.y;
            comp->render_bounds.w = comp->bounds.w * elem->render_bounds.w;
            comp->render_bounds.h = comp->bounds.h * elem->render_bounds.h;

            if (comp->type == VIDEO_LAYOUT_C_SCREEN)
               view->screens[comp->attr.screen.index] = comp->render_bounds;
         }
      }
   }
}