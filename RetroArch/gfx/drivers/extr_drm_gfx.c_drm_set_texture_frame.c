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
typedef  int uint16_t ;
struct drm_video {int /*<<< orphan*/  menu_surface; int /*<<< orphan*/  current_aspect; int /*<<< orphan*/  menu_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  drm_plane_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_surface_setup (struct drm_video*,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_surface_update (struct drm_video*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 

__attribute__((used)) static void drm_set_texture_frame(void *data, const void *frame, bool rgb32,
      unsigned width, unsigned height, float alpha)
{
   unsigned int i, j;
   struct drm_video *_drmvars = data;

   if (!_drmvars->menu_active)
      return;

   /* If menu is active in this frame but the
    * menu surface is NULL, we allocate a new one.*/
   if (!_drmvars->menu_surface)
   {
      drm_surface_setup(_drmvars,
            width,
            height,
            width * 4,
            4,
            DRM_FORMAT_XRGB8888,
            210,
            _drmvars->current_aspect,
            2,
            0,
            &_drmvars->menu_surface);

      /* We need to re-setup the ONLY plane as the setup
       * depends on input buffers dimensions. */
      drm_plane_setup(_drmvars->menu_surface);
   }

   /* We have to go on a pixel format conversion adventure
    * for now, until we can convince RGUI to output
    * in an 8888 format. */
   unsigned int src_pitch        = width * 2;
   unsigned int dst_pitch        = width * 4;
   unsigned int dst_width        = width;
   uint32_t line[dst_width];

   /* The output pixel array with the converted pixels. */
   char *frame_output = (char *) malloc (dst_pitch * height);

   /* Remember, memcpy() works with 8bits pointers for increments. */
   char *dst_base_addr           = frame_output;

   for (i = 0; i < height; i++)
   {
      for (j = 0; j < src_pitch / 2; j++)
      {
         uint16_t src_pix = *((uint16_t*)frame + (src_pitch / 2 * i) + j);
         /* The hex AND is for keeping only the part we need for each component. */
         uint32_t R = (src_pix << 8) & 0x00FF0000;
         uint32_t G = (src_pix << 4) & 0x0000FF00;
         uint32_t B = (src_pix << 0) & 0x000000FF;
         line[j] = (0 | R | G | B);
      }
      memcpy(dst_base_addr + (dst_pitch * i), (char*)line, dst_pitch);
   }

   /* We update the menu surface if menu is active. */
   drm_surface_update(_drmvars, frame_output, _drmvars->menu_surface);
}