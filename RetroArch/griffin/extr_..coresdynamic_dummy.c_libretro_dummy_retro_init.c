#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {int menu_rgui_aspect_ratio; } ;
struct TYPE_5__ {int /*<<< orphan*/  menu_driver; } ;
struct TYPE_7__ {TYPE_2__ uints; TYPE_1__ arrays; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
#define  RGUI_ASPECT_RATIO_16_10 131 
#define  RGUI_ASPECT_RATIO_16_10_CENTRE 130 
#define  RGUI_ASPECT_RATIO_16_9 129 
#define  RGUI_ASPECT_RATIO_16_9_CENTRE 128 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 int* dummy_frame_buf ; 
 int frame_buf_height ; 
 int frame_buf_width ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 

void libretro_dummy_retro_init(void)
{
#if defined(HAVE_MENU) && defined(HAVE_RGUI)
   settings_t *settings = config_get_ptr();
#endif
   unsigned i;

   /* Sensible defaults */
   frame_buf_width = 320;
   frame_buf_height = 240;

#if defined(HAVE_MENU) && defined(HAVE_RGUI)
   if (string_is_equal(settings->arrays.menu_driver, "rgui"))
   {
      switch (settings->uints.menu_rgui_aspect_ratio)
      {
         case RGUI_ASPECT_RATIO_16_9:
         case RGUI_ASPECT_RATIO_16_9_CENTRE:
            frame_buf_width = 426;
            break;
         case RGUI_ASPECT_RATIO_16_10:
         case RGUI_ASPECT_RATIO_16_10_CENTRE:
            frame_buf_width = 384;
            break;
         default:
            /* 4:3 */
            frame_buf_width = 320;
            break;
      }
   }
#endif

   dummy_frame_buf = (uint16_t*)calloc(frame_buf_width * frame_buf_height, sizeof(uint16_t));
   for (i = 0; i < (unsigned)(frame_buf_width * frame_buf_height); i++)
      dummy_frame_buf[i] = 4 << 5;
}