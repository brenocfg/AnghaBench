#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int digits; int max_state; void* align; } ;
struct TYPE_10__ {void* align; int /*<<< orphan*/ * string; } ;
struct TYPE_9__ {int loaded; int /*<<< orphan*/  alpha_idx; int /*<<< orphan*/  image_idx; int /*<<< orphan*/ * alpha_file; int /*<<< orphan*/ * file; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
struct TYPE_12__ {TYPE_4__ counter; TYPE_3__ text; TYPE_2__ image; TYPE_1__ screen; } ;
struct TYPE_13__ {int type; int enabled_state; TYPE_5__ attr; int /*<<< orphan*/  color; int /*<<< orphan*/  orientation; int /*<<< orphan*/  render_bounds; int /*<<< orphan*/  bounds; } ;
typedef  TYPE_6__ component_t ;
typedef  int comp_type_t ;

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
 int /*<<< orphan*/  VIDEO_LAYOUT_ROT0 ; 
 void* VIDEO_LAYOUT_TEXT_ALIGN_CENTER ; 
 int /*<<< orphan*/  make_bounds () ; 
 int /*<<< orphan*/  make_bounds_unit () ; 
 int /*<<< orphan*/  make_color_white () ; 

void component_init(component_t *comp, comp_type_t type)
{
   comp->type = type;
   comp->bounds = make_bounds();
   comp->render_bounds = make_bounds_unit();
   comp->orientation = VIDEO_LAYOUT_ROT0;
   comp->color = make_color_white();
   comp->enabled_state = -1;

   switch (comp->type)
   {
      case VIDEO_LAYOUT_C_UNKNOWN:
         break;
      case VIDEO_LAYOUT_C_SCREEN:
         comp->attr.screen.index = 0;
         break;
      case VIDEO_LAYOUT_C_RECT:
         break;
      case VIDEO_LAYOUT_C_DISK:
         break;
      case VIDEO_LAYOUT_C_IMAGE:
         comp->attr.image.file = NULL;
         comp->attr.image.alpha_file = NULL;
         comp->attr.image.image_idx = 0;
         comp->attr.image.alpha_idx = 0;
         comp->attr.image.loaded = false;
         break;
      case VIDEO_LAYOUT_C_TEXT:
         comp->attr.text.string = NULL;
         comp->attr.text.align = VIDEO_LAYOUT_TEXT_ALIGN_CENTER;
         break;
      case VIDEO_LAYOUT_C_COUNTER:
         comp->attr.counter.digits = 2;
         comp->attr.counter.max_state = 999;
         comp->attr.counter.align = VIDEO_LAYOUT_TEXT_ALIGN_CENTER;
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