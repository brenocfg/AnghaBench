#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int layers_count; TYPE_2__* layers; } ;
typedef  TYPE_1__ view_t ;
struct TYPE_7__ {void* blend; } ;
typedef  TYPE_2__ layer_t ;

/* Variables and functions */
 void* VIDEO_LAYOUT_BLEND_ADD ; 
 void* VIDEO_LAYOUT_BLEND_ALPHA ; 
 void* VIDEO_LAYOUT_BLEND_MOD ; 
 TYPE_2__* view_find_layer (TYPE_1__*,char*) ; 

void view_sort_layers(view_t *view)
{
   layer_t sorted[6];
   layer_t *layer;
   int i = 0;

   /* retroarch frame *= screen's color */
   if ((layer = view_find_layer(view, "screen")))
   {
      layer->blend = VIDEO_LAYOUT_BLEND_MOD;
      sorted[i] = *layer;
      ++i;
   }

   if ((layer = view_find_layer(view, "overlay")))
   {
      layer->blend = VIDEO_LAYOUT_BLEND_MOD;
      sorted[i] = *layer;
      ++i;
   }

   if ((layer = view_find_layer(view, "backdrop")))
   {
      layer->blend = VIDEO_LAYOUT_BLEND_ADD;
      sorted[i] = *layer;
      ++i;
   }

   if ((layer = view_find_layer(view, "bezel")))
   {
      layer->blend = VIDEO_LAYOUT_BLEND_ALPHA;
      sorted[i] = *layer;
      ++i;
   }

   if ((layer = view_find_layer(view, "cpanel")))
   {
      layer->blend = VIDEO_LAYOUT_BLEND_ALPHA;
      sorted[i] = *layer;
      ++i;
   }

   if ((layer = view_find_layer(view, "marquee")))
   {
      layer->blend = VIDEO_LAYOUT_BLEND_ALPHA;
      sorted[i] = *layer;
      ++i;
   }

   for (i = 0; i < view->layers_count; ++i)
      view->layers[i] = sorted[i];
}