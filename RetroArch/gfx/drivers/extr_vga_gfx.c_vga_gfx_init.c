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
struct TYPE_3__ {int width; int /*<<< orphan*/  is_threaded; scalar_t__ font_enable; scalar_t__ rgb32; int /*<<< orphan*/  height; } ;
typedef  TYPE_1__ video_info_t ;
typedef  void vga_t ;
typedef  int /*<<< orphan*/  input_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_DRIVER_RENDER_VGA ; 
 int VGA_HEIGHT ; 
 int VGA_WIDTH ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  font_driver_init_osd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 unsigned char* vga_frame ; 
 int /*<<< orphan*/  vga_gfx_create () ; 
 scalar_t__ vga_rgb32 ; 
 int vga_video_bits ; 
 int /*<<< orphan*/  vga_video_height ; 
 int vga_video_pitch ; 
 int vga_video_width ; 

__attribute__((used)) static void *vga_gfx_init(const video_info_t *video,
      input_driver_t **input, void **input_data)
{
   vga_t *vga        = (vga_t*)calloc(1, sizeof(*vga));

   *input              = NULL;
   *input_data         = NULL;

   vga_video_width    = video->width;
   vga_video_height   = video->height;
   vga_rgb32          = video->rgb32;

   if (video->rgb32)
   {
      vga_video_pitch = video->width * 4;
      vga_video_bits = 32;
   }
   else
   {
      vga_video_pitch = video->width * 2;
      vga_video_bits = 16;
   }

   vga_frame = (unsigned char*)malloc(VGA_WIDTH * VGA_HEIGHT);

   vga_gfx_create();

   if (video->font_enable)
      font_driver_init_osd(NULL, false,
            video->is_threaded, FONT_DRIVER_RENDER_VGA);

   return vga;
}