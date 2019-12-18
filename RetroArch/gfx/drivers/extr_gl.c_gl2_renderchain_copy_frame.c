#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ use_rgba; } ;
typedef  TYPE_1__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {size_t tex_w; size_t tex_h; size_t tex_index; size_t base_size; void const* conv_buffer; int /*<<< orphan*/  texture_fmt; int /*<<< orphan*/  texture_type; int /*<<< orphan*/  scaler; int /*<<< orphan*/  have_es2_compat; scalar_t__ support_unpack_row_length; } ;
typedef  TYPE_2__ gl_t ;
struct TYPE_11__ {scalar_t__ egl_images; } ;
typedef  TYPE_3__ gl2_renderchain_data_t ;
struct TYPE_12__ {unsigned int width; unsigned int height; unsigned int pitch; size_t index; int rgb32; scalar_t__* handle; void const* frame; } ;
typedef  TYPE_4__ gfx_ctx_image_t ;
typedef  void GLvoid ;
typedef  int /*<<< orphan*/  GLeglImageOES ;
typedef  scalar_t__ EGLImageKHR ;

/* Variables and functions */
 scalar_t__ EGL_NO_IMAGE_KHR ; 
 int /*<<< orphan*/  GL_READ_WRITE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_REFERENCE_BUFFER_SCE ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNPACK_ROW_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  glEGLImageTargetTexture2DOES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ glMapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  glTexSubImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  glUnmapBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int const) ; 
 int video_context_driver_write_to_image_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  video_frame_convert_argb8888_to_abgr8888 (int /*<<< orphan*/ *,void const*,void const*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  video_frame_convert_rgb16_to_rgb32 (int /*<<< orphan*/ *,void*,void const*,unsigned int,unsigned int,unsigned int) ; 
 unsigned int video_pixel_get_alignment (unsigned int) ; 

__attribute__((used)) static void gl2_renderchain_copy_frame(
      gl_t *gl,
      gl2_renderchain_data_t *chain,
      video_frame_info_t *video_info,
      const void *frame,
      unsigned width, unsigned height, unsigned pitch)
{
#if defined(HAVE_PSGL)
   {
      unsigned h;
      size_t buffer_addr        = gl->tex_w * gl->tex_h *
         gl->tex_index * gl->base_size;
      size_t buffer_stride      = gl->tex_w * gl->base_size;
      const uint8_t *frame_copy = frame;
      size_t frame_copy_size    = width * gl->base_size;
      uint8_t           *buffer = (uint8_t*)glMapBuffer(
            GL_TEXTURE_REFERENCE_BUFFER_SCE, GL_READ_WRITE) + buffer_addr;
      for (h = 0; h < height; h++, buffer += buffer_stride, frame_copy += pitch)
         memcpy(buffer, frame_copy, frame_copy_size);

      glUnmapBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE);
   }
#elif defined(HAVE_OPENGLES)
#if defined(HAVE_EGL)
   if (chain->egl_images)
   {
      gfx_ctx_image_t img_info;
      bool new_egl    = false;
      EGLImageKHR img = 0;

      img_info.frame  = frame;
      img_info.width  = width;
      img_info.height = height;
      img_info.pitch  = pitch;
      img_info.index  = gl->tex_index;
      img_info.rgb32  = (gl->base_size == 4);
      img_info.handle = &img;

      new_egl         =
         video_context_driver_write_to_image_buffer(&img_info);

      if (img == EGL_NO_IMAGE_KHR)
      {
         RARCH_ERR("[GL]: Failed to create EGL image.\n");
         return;
      }

      if (new_egl)
         glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, (GLeglImageOES)img);
   }
   else
#endif
   {
      glPixelStorei(GL_UNPACK_ALIGNMENT,
            video_pixel_get_alignment(width * gl->base_size));

      /* Fallback for GLES devices without GL_BGRA_EXT. */
      if (gl->base_size == 4 && video_info->use_rgba)
      {
         video_frame_convert_argb8888_to_abgr8888(
               &gl->scaler,
               gl->conv_buffer,
               frame, width, height, pitch);
         glTexSubImage2D(GL_TEXTURE_2D,
               0, 0, 0, width, height, gl->texture_type,
               gl->texture_fmt, gl->conv_buffer);
      }
      else if (gl->support_unpack_row_length)
      {
         glPixelStorei(GL_UNPACK_ROW_LENGTH, pitch / gl->base_size);
         glTexSubImage2D(GL_TEXTURE_2D,
               0, 0, 0, width, height, gl->texture_type,
               gl->texture_fmt, frame);

         glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
      }
      else
      {
         /* No GL_UNPACK_ROW_LENGTH. */

         const GLvoid *data_buf = frame;
         unsigned pitch_width   = pitch / gl->base_size;

         if (width != pitch_width)
         {
            /* Slow path - conv_buffer is preallocated
             * just in case we hit this path. */

            unsigned h;
            const unsigned line_bytes = width * gl->base_size;
            uint8_t *dst              = (uint8_t*)gl->conv_buffer;
            const uint8_t *src        = (const uint8_t*)frame;

            for (h = 0; h < height; h++, src += pitch, dst += line_bytes)
               memcpy(dst, src, line_bytes);

            data_buf                  = gl->conv_buffer;
         }

         glTexSubImage2D(GL_TEXTURE_2D,
               0, 0, 0, width, height, gl->texture_type,
               gl->texture_fmt, data_buf);
      }
   }
#else
   {
      const GLvoid *data_buf = frame;
      glPixelStorei(GL_UNPACK_ALIGNMENT, video_pixel_get_alignment(pitch));

      if (gl->base_size == 2 && !gl->have_es2_compat)
      {
         /* Convert to 32-bit textures on desktop GL.
          *
          * It is *much* faster (order of magnitude on my setup)
          * to use a custom SIMD-optimized conversion routine
          * than letting GL do it. */
         video_frame_convert_rgb16_to_rgb32(
               &gl->scaler,
               gl->conv_buffer,
               frame,
               width,
               height,
               pitch);
         data_buf = gl->conv_buffer;
      }
      else
         glPixelStorei(GL_UNPACK_ROW_LENGTH, pitch / gl->base_size);

      glTexSubImage2D(GL_TEXTURE_2D,
            0, 0, 0, width, height, gl->texture_type,
            gl->texture_fmt, data_buf);

      glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
   }
#endif
}