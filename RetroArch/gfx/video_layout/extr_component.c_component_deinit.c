#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {int /*<<< orphan*/  alpha_file; int /*<<< orphan*/  file; } ;
struct TYPE_8__ {TYPE_2__ text; TYPE_1__ image; } ;
struct TYPE_9__ {int type; TYPE_3__ attr; } ;
typedef  TYPE_4__ component_t ;

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
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void component_deinit(component_t *comp)
{
   switch (comp->type)
   {
      case VIDEO_LAYOUT_C_UNKNOWN:
         break;
      case VIDEO_LAYOUT_C_SCREEN:
         break;
      case VIDEO_LAYOUT_C_RECT:
         break;
      case VIDEO_LAYOUT_C_DISK:
         break;
      case VIDEO_LAYOUT_C_IMAGE:
         free(comp->attr.image.file);
         free(comp->attr.image.alpha_file);
         break;
      case VIDEO_LAYOUT_C_TEXT:
         free(comp->attr.text.string);
         break;
      case VIDEO_LAYOUT_C_COUNTER:
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