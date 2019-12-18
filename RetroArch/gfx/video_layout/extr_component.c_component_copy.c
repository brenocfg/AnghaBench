#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  align; int /*<<< orphan*/  max_state; int /*<<< orphan*/  digits; } ;
struct TYPE_11__ {int /*<<< orphan*/  align; void* string; } ;
struct TYPE_10__ {int /*<<< orphan*/  loaded; int /*<<< orphan*/  alpha_idx; int /*<<< orphan*/  image_idx; void* alpha_file; void* file; } ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
struct TYPE_13__ {TYPE_4__ counter; TYPE_3__ text; TYPE_2__ image; TYPE_1__ screen; } ;
struct TYPE_14__ {int type; TYPE_5__ attr; int /*<<< orphan*/  enabled_state; int /*<<< orphan*/  color; int /*<<< orphan*/  orientation; int /*<<< orphan*/  render_bounds; int /*<<< orphan*/  bounds; } ;
typedef  TYPE_6__ component_t ;

/* Variables and functions */
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
 void* init_string (void*) ; 

void component_copy(component_t *comp, const component_t *src)
{
   comp->type = src->type;
   comp->bounds = src->bounds;
   comp->render_bounds = src->render_bounds;
   comp->orientation = src->orientation;
   comp->color = src->color;
   comp->enabled_state = src->enabled_state;

   switch (comp->type)
   {
      case VIDEO_LAYOUT_C_UNKNOWN:
         break;
      case VIDEO_LAYOUT_C_SCREEN:
         comp->attr.screen.index = src->attr.screen.index;
         break;
      case VIDEO_LAYOUT_C_RECT:
         break;
      case VIDEO_LAYOUT_C_DISK:
         break;
      case VIDEO_LAYOUT_C_IMAGE:
         comp->attr.image.file = init_string(src->attr.image.file);
         comp->attr.image.alpha_file = init_string(src->attr.image.alpha_file);
         comp->attr.image.image_idx = src->attr.image.image_idx;
         comp->attr.image.alpha_idx = src->attr.image.alpha_idx;
         comp->attr.image.loaded = src->attr.image.loaded;
         break;
      case VIDEO_LAYOUT_C_TEXT:
         comp->attr.text.string = init_string(src->attr.text.string);
         comp->attr.text.align = src->attr.text.align;
         break;
      case VIDEO_LAYOUT_C_COUNTER:
         comp->attr.counter.digits = src->attr.counter.digits;
         comp->attr.counter.max_state = src->attr.counter.max_state;
         comp->attr.counter.align = src->attr.counter.align;
         break;
      case VIDEO_LAYOUT_C_DOTMATRIX_X1:
         break;
      case VIDEO_LAYOUT_C_DOTMATRIX_H5:
         break;
      case VIDEO_LAYOUT_C_DOTMATRIX_H8:
         break;
      case VIDEO_LAYOUT_C_LED_7:
         break;
      case VIDEO_LAYOUT_C_LED_8_GTS1:
         break;
      case VIDEO_LAYOUT_C_LED_14:
         break;
      case VIDEO_LAYOUT_C_LED_14_SC:
         break;
      case VIDEO_LAYOUT_C_LED_16:
         break;
      case VIDEO_LAYOUT_C_LED_16_SC:
         break;
      case VIDEO_LAYOUT_C_REEL:
         break;
   }
}