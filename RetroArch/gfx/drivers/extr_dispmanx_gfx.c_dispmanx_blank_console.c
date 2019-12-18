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
typedef  int uint16_t ;
struct dispmanx_video {int /*<<< orphan*/  back_surface; scalar_t__ dispmanx_height; scalar_t__ dispmanx_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_IMAGE_RGB565 ; 
 int /*<<< orphan*/  dispmanx_surface_setup (struct dispmanx_video*,int,int,int,int,int /*<<< orphan*/ ,int,float,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispmanx_surface_update_async (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispmanx_blank_console (struct dispmanx_video *_dispvars)
{
   /* Since pitch will be aligned to 16 pixels (not bytes) we use a
    * 16 pixels image to save the alignment */
   uint16_t image[16] = {0x0000};
   float aspect = (float)_dispvars->dispmanx_width / (float)_dispvars->dispmanx_height;

   dispmanx_surface_setup(_dispvars,
         16,
         1,
         32,
         16,
         VC_IMAGE_RGB565,
         255,
         aspect,
         1,
         -1,
         &_dispvars->back_surface);

   /* Updating 1-page surface synchronously asks for truble, since the 1st CB will
    * signal but not free because the only page is on screen, so get_free will wait forever. */
   dispmanx_surface_update_async(image, _dispvars->back_surface);
}