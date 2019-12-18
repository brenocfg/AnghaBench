#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GRAPHICS_RESOURCE_HEIGHT ; 
 int /*<<< orphan*/  GRAPHICS_RESOURCE_RGBA32 ; 
 int /*<<< orphan*/  GRAPHICS_RESOURCE_WIDTH ; 
 int /*<<< orphan*/  GRAPHICS_RGBA32 (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  VC_DISPMAN_ROT0 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcm_host_init () ; 
 int /*<<< orphan*/  graphics_delete_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  graphics_display_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int graphics_get_display_size (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  graphics_resource_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  graphics_update_displayed_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gx_create_window (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gx_graphics_init (char*) ; 
 int /*<<< orphan*/  render_subtitle (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int) ; 

int main(void)
{
   GRAPHICS_RESOURCE_HANDLE img;
   uint32_t width, height;
   int LAYER=1;
   bcm_host_init();
   int s;

   s = gx_graphics_init(".");
   assert(s == 0);

   s = graphics_get_display_size(0, &width, &height);
   assert(s == 0);

   s = gx_create_window(0, width, height, GRAPHICS_RESOURCE_RGBA32, &img);
   assert(s == 0);

   // transparent before display to avoid screen flash
   graphics_resource_fill(img, 0, 0, width, height, GRAPHICS_RGBA32(0,0,0,0x00));

   graphics_display_resource(img, 0, LAYER, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, VC_DISPMAN_ROT0, 1);

   uint32_t text_size = 10;
   while (1) {
      const char *text = "The quick brown fox jumps over the lazy dog";
      uint32_t y_offset = height-60+text_size/2;
      graphics_resource_fill(img, 0, 0, width, height, GRAPHICS_RGBA32(0,0,0,0x00));
      // blue, at the top (y=40)
      graphics_resource_fill(img, 0, 40, width, 1, GRAPHICS_RGBA32(0,0,0xff,0xff));

      // green, at the bottom (y=height-40)
      graphics_resource_fill(img, 0, height-40, width, 1, GRAPHICS_RGBA32(0,0xff,0,0xff));

      // draw the subtitle text
      render_subtitle(img, text, 0, text_size,  y_offset);
      graphics_update_displayed_resource(img, 0, 0, 0, 0);
      text_size += 1;
      if (text_size > 50)
         text_size = 10;
   }

   graphics_display_resource(img, 0, LAYER, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, VC_DISPMAN_ROT0, 0);
   graphics_delete_resource(img);

   return 0;
}