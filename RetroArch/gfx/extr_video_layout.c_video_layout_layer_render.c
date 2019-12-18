#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
struct TYPE_42__ {int /*<<< orphan*/  (* layer_end ) (TYPE_9__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* led_seg ) (TYPE_9__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* led_dot ) (TYPE_9__*,int,int) ;int /*<<< orphan*/  (* counter ) (TYPE_9__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* text ) (TYPE_9__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* image ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ellipse ) (TYPE_9__*) ;int /*<<< orphan*/  (* rect ) (TYPE_9__*) ;int /*<<< orphan*/  (* screen ) (TYPE_9__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* layer_begin ) (TYPE_9__*) ;} ;
typedef  TYPE_8__ video_layout_render_interface_t ;
struct TYPE_43__ {int /*<<< orphan*/  color; int /*<<< orphan*/  orientation; int /*<<< orphan*/  bounds; void* video_driver_frame_data; } ;
typedef  TYPE_9__ video_layout_render_info_t ;
struct TYPE_31__ {int elements_count; int /*<<< orphan*/  blend; TYPE_11__* elements; } ;
typedef  TYPE_10__ layer_t ;
struct TYPE_32__ {int o_bind; int state; int components_count; TYPE_12__* components; } ;
typedef  TYPE_11__ element_t ;
struct TYPE_40__ {int /*<<< orphan*/  max_state; } ;
struct TYPE_39__ {int /*<<< orphan*/  string; } ;
struct TYPE_38__ {int loaded; size_t image_idx; size_t alpha_idx; int /*<<< orphan*/  alpha_file; int /*<<< orphan*/  file; } ;
struct TYPE_37__ {int /*<<< orphan*/  index; } ;
struct TYPE_41__ {TYPE_6__ counter; TYPE_5__ text; TYPE_4__ image; TYPE_3__ screen; } ;
struct TYPE_33__ {int enabled_state; int type; TYPE_7__ attr; int /*<<< orphan*/  color; int /*<<< orphan*/  orientation; int /*<<< orphan*/  render_bounds; } ;
typedef  TYPE_12__ component_t ;
struct TYPE_36__ {int value; } ;
struct TYPE_35__ {TYPE_10__* layers; } ;
struct TYPE_34__ {int /*<<< orphan*/ * images; TYPE_2__* io; TYPE_1__* view; TYPE_8__* render; TYPE_9__ render_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
#define  VIDEO_LAYOUT_C_COUNTER 144 
#define  VIDEO_LAYOUT_C_DISK 143 
#define  VIDEO_LAYOUT_C_DOTMATRIX_H5 142 
#define  VIDEO_LAYOUT_C_DOTMATRIX_H8 141 
#define  VIDEO_LAYOUT_C_DOTMATRIX_X1 140 
#define  VIDEO_LAYOUT_C_IMAGE 139 
#define  VIDEO_LAYOUT_C_LED_14 138 
#define  VIDEO_LAYOUT_C_LED_14_SC 137 
#define  VIDEO_LAYOUT_C_LED_16 136 
#define  VIDEO_LAYOUT_C_LED_16_SC 135 
#define  VIDEO_LAYOUT_C_LED_7 134 
#define  VIDEO_LAYOUT_C_LED_8_GTS1 133 
#define  VIDEO_LAYOUT_C_RECT 132 
#define  VIDEO_LAYOUT_C_REEL 131 
#define  VIDEO_LAYOUT_C_SCREEN 130 
#define  VIDEO_LAYOUT_C_TEXT 129 
#define  VIDEO_LAYOUT_C_UNKNOWN 128 
 int /*<<< orphan*/  VIDEO_LAYOUT_LED_14 ; 
 int /*<<< orphan*/  VIDEO_LAYOUT_LED_14_SC ; 
 int /*<<< orphan*/  VIDEO_LAYOUT_LED_16 ; 
 int /*<<< orphan*/  VIDEO_LAYOUT_LED_16_SC ; 
 int /*<<< orphan*/  VIDEO_LAYOUT_LED_7 ; 
 int /*<<< orphan*/  VIDEO_LAYOUT_LED_8_GTS1 ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*) ; 
 int /*<<< orphan*/  stub10 (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  stub11 (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub12 (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub15 (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub16 (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub17 (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_9__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_9__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  stub9 (TYPE_9__*,int,int) ; 
 void* video_layout_load_image (int /*<<< orphan*/ ) ; 
 TYPE_13__* video_layout_state ; 

void video_layout_layer_render(void *video_driver_frame_data, int index)
{
   video_layout_render_info_t *info;
   const video_layout_render_interface_t *r;
   layer_t *layer;
   int i, j;
   
   info  = &video_layout_state->render_info;
   r     =  video_layout_state->render;
   layer = &video_layout_state->view->layers[index];

   info->video_driver_frame_data = video_driver_frame_data;

   r->layer_begin(info);

   for (i = 0; i < layer->elements_count; ++i)
   {
      element_t *elem;
      elem = &layer->elements[i];

      if (elem->o_bind != -1)
         elem->state = video_layout_state->io[elem->o_bind].value;

      for (j = 0; j < elem->components_count; ++j)
      {
         component_t *comp;
         comp = &elem->components[j];

         if (comp->enabled_state != -1)
         {
            if(comp->enabled_state != elem->state)
               continue;
         }

         info->bounds = comp->render_bounds;
         info->orientation = comp->orientation;
         info->color = comp->color;

         switch (comp->type)
         {
         case VIDEO_LAYOUT_C_UNKNOWN:
            break;
         case VIDEO_LAYOUT_C_SCREEN:
            r->screen(info, comp->attr.screen.index);
            break;
         case VIDEO_LAYOUT_C_RECT:
            r->rect(info);
            break;
         case VIDEO_LAYOUT_C_DISK:
            r->ellipse(info);
            break;
         case VIDEO_LAYOUT_C_IMAGE:
            if(!comp->attr.image.loaded)
            {
               comp->attr.image.image_idx = video_layout_load_image(comp->attr.image.file);
               if(comp->attr.image.alpha_file)
                  comp->attr.image.alpha_idx = video_layout_load_image(comp->attr.image.alpha_file);
               comp->attr.image.loaded = true;
            }
            r->image(info,
               video_layout_state->images[comp->attr.image.image_idx],
               video_layout_state->images[comp->attr.image.alpha_idx]);
            break;
         case VIDEO_LAYOUT_C_TEXT:
            r->text(info, comp->attr.text.string);
            break;
         case VIDEO_LAYOUT_C_COUNTER:
            r->counter(info, MIN(elem->state, comp->attr.counter.max_state));
            break;
         case VIDEO_LAYOUT_C_DOTMATRIX_X1:
            r->led_dot(info, 1, elem->state);
            break;
         case VIDEO_LAYOUT_C_DOTMATRIX_H5:
            r->led_dot(info, 5, elem->state);
            break;
         case VIDEO_LAYOUT_C_DOTMATRIX_H8:
            r->led_dot(info, 8, elem->state);
            break;
         case VIDEO_LAYOUT_C_LED_7:
            r->led_seg(info, VIDEO_LAYOUT_LED_7, elem->state);
            break;
         case VIDEO_LAYOUT_C_LED_8_GTS1:
            r->led_seg(info, VIDEO_LAYOUT_LED_8_GTS1, elem->state);
            break;
         case VIDEO_LAYOUT_C_LED_14:
            r->led_seg(info, VIDEO_LAYOUT_LED_14, elem->state);
            break;
         case VIDEO_LAYOUT_C_LED_14_SC:
            r->led_seg(info, VIDEO_LAYOUT_LED_14_SC, elem->state);
            break;
         case VIDEO_LAYOUT_C_LED_16:
            r->led_seg(info, VIDEO_LAYOUT_LED_16, elem->state);
            break;
         case VIDEO_LAYOUT_C_LED_16_SC:
            r->led_seg(info, VIDEO_LAYOUT_LED_16_SC, elem->state);
            break;
         case VIDEO_LAYOUT_C_REEL:
            /* not implemented */
            break;
         }
      }
   }

   r->layer_end(info, layer->blend);
}