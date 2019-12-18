#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_3__ {float r; float g; float b; float a; } ;
typedef  TYPE_1__ menu_display_ctx_clearcolor_t ;

/* Variables and functions */
 int /*<<< orphan*/  RGBA8 (int,int,int,int) ; 
 int /*<<< orphan*/  wiiu_clear_screen () ; 
 int /*<<< orphan*/  wiiu_set_clear_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void menu_display_wiiu_clear_color(
      menu_display_ctx_clearcolor_t *clearcolor,
      video_frame_info_t *video_info)
{
   if (!clearcolor)
      return;
#if 0
   wiiu_set_clear_color(RGBA8((int)(clearcolor->r*255.f),
            (int)(clearcolor->g*255.f),
            (int)(clearcolor->b*255.f),
            (int)(clearcolor->a*255.f)));
   wiiu_clear_screen();
#endif
}