#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int opts; int /*<<< orphan*/  num_swaps; int /*<<< orphan*/  surface; int /*<<< orphan*/  display; TYPE_2__* slots; int /*<<< orphan*/  texture; } ;
typedef  TYPE_1__ VIDTEX_T ;
struct TYPE_10__ {void* video_frame; void* image; } ;
typedef  TYPE_2__ VIDTEX_IMAGE_SLOT_T ;
typedef  int GLfloat ;
typedef  int /*<<< orphan*/  EGLenum ;
typedef  void* EGLImageKHR ;
typedef  int /*<<< orphan*/  EGLClientBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_IMAGE_BRCM_MULTIMEDIA ; 
 int /*<<< orphan*/  EGL_IMAGE_BRCM_MULTIMEDIA_U ; 
 int /*<<< orphan*/  EGL_IMAGE_BRCM_MULTIMEDIA_V ; 
 int /*<<< orphan*/  EGL_IMAGE_BRCM_MULTIMEDIA_Y ; 
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 void* EGL_NO_IMAGE_KHR ; 
 int /*<<< orphan*/  GL_COLOR_ARRAY ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_EXTERNAL_OES ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 int /*<<< orphan*/  VIDTEX_CHECK_GL (TYPE_1__*) ; 
 int VIDTEX_OPT_IMG_PER_FRAME ; 
 int VIDTEX_OPT_U_TEXTURE ; 
 int VIDTEX_OPT_V_TEXTURE ; 
 int VIDTEX_OPT_Y_TEXTURE ; 
 void* eglCreateImageKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearDepthf (int) ; 
 int /*<<< orphan*/  glDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEGLImageTargetTexture2DOES (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  glEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glRotatef (int,double,double,double) ; 
 int /*<<< orphan*/  glTexCoordPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  glVertexPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (void*) ; 
 int vcos_countof (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_log_error (char*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,void*,void*) ; 
 int /*<<< orphan*/  vidtex_destroy_images (TYPE_1__*) ; 
 TYPE_2__* vt_tex_coords ; 
 int /*<<< orphan*/  vt_vertices ; 

__attribute__((used)) static void vidtex_draw(VIDTEX_T *vt, void *video_frame)
{
   EGLImageKHR image;
   VIDTEX_IMAGE_SLOT_T *slot;
   static uint32_t frame_num = 0;

   vcos_assert(video_frame);

   glClearColor(0, 0, 0, 0);
   glClearDepthf(1);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   glBindTexture(GL_TEXTURE_EXTERNAL_OES, vt->texture);
   VIDTEX_CHECK_GL(vt);

   /* Lookup or create EGL image corresponding to supplied buffer handle.
    * N.B. Slot array is filled in sequentially, with the images all destroyed together on
    *      vidtex termination; it never has holes. */
   image = EGL_NO_IMAGE_KHR;

   for (slot = vt->slots; slot < vt->slots + vcos_countof(vt->slots); slot++)
   {
      if (slot->video_frame == video_frame)
      {
         vcos_assert(slot->image);
         image = slot->image;
         break;
      }

      if (slot->video_frame == NULL)
      {
         EGLenum target;
         vcos_assert(slot->image == NULL);

         if (vt->opts & VIDTEX_OPT_Y_TEXTURE)
            target = EGL_IMAGE_BRCM_MULTIMEDIA_Y;
         else if (vt->opts & VIDTEX_OPT_U_TEXTURE)
            target = EGL_IMAGE_BRCM_MULTIMEDIA_U;
         else if (vt->opts & VIDTEX_OPT_V_TEXTURE)
            target = EGL_IMAGE_BRCM_MULTIMEDIA_V;
         else
            target = EGL_IMAGE_BRCM_MULTIMEDIA;

         image = eglCreateImageKHR(vt->display, EGL_NO_CONTEXT, target,
               (EGLClientBuffer)video_frame, NULL);
         if (image == EGL_NO_IMAGE_KHR)
         {
            vcos_log_error("EGL image conversion error");
         }
         else
         {
            vcos_log_trace("Created EGL image %p for buf %p", image, video_frame);
            slot->video_frame = video_frame;
            slot->image = image;
         }
         VIDTEX_CHECK_GL(vt);

         break;
      }
   }

   if (slot == vt->slots + vcos_countof(vt->slots))
   {
      vcos_log_error("Exceeded configured max number of EGL images");
   }

   /* Draw the EGL image */
   if (image != EGL_NO_IMAGE_KHR)
   {
      /* Assume 30fps */
      int frames_per_rev = 30 * 15;
      GLfloat angle = (frame_num * 360) / (GLfloat) frames_per_rev;
      frame_num = (frame_num + 1) % frames_per_rev;

      glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, image);
      VIDTEX_CHECK_GL(vt);

      glRotatef(angle, 0.0, 0.0, 1.0);
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, 0, vt_vertices);
      glDisableClientState(GL_COLOR_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, vt_tex_coords);

      glDrawArrays(GL_TRIANGLES, 0, vcos_countof(vt_tex_coords) / 2);

      eglSwapBuffers(vt->display, vt->surface);

      if (vt->opts & VIDTEX_OPT_IMG_PER_FRAME)
      {
         vidtex_destroy_images(vt);
      }

      vt->num_swaps++;
   }

   VIDTEX_CHECK_GL(vt);
}