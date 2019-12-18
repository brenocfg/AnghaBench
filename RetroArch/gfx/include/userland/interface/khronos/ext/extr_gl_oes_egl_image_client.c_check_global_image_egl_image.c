#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  global_image_egl_images; scalar_t__ inited; } ;
struct TYPE_8__ {TYPE_1__* context; } ;
struct TYPE_9__ {TYPE_2__ opengl; } ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLeglImageOES ;
typedef  TYPE_3__ CLIENT_THREAD_STATE_T ;
typedef  TYPE_4__ CLIENT_PROCESS_STATE_T ;

/* Variables and functions */
 TYPE_4__* CLIENT_GET_PROCESS_STATE () ; 
 int /*<<< orphan*/  CLIENT_LOCK () ; 
 int /*<<< orphan*/  CLIENT_UNLOCK () ; 
 scalar_t__ EGL_PIXEL_FORMAT_GLES2_TEXTURE_BRCM ; 
 scalar_t__ EGL_PIXEL_FORMAT_GLES_TEXTURE_BRCM ; 
 scalar_t__ EGL_PIXEL_FORMAT_RENDER_GLES2_BRCM ; 
 scalar_t__ EGL_PIXEL_FORMAT_RENDER_GLES_BRCM ; 
 scalar_t__ OPENGL_ES_11 ; 
 int khrn_global_image_map_lookup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  platform_get_global_image_info (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static bool check_global_image_egl_image(GLuint global_image_id[2],
   GLeglImageOES image, CLIENT_THREAD_STATE_T *thread,
   bool render) /* else texture */
{
   CLIENT_PROCESS_STATE_T *process = CLIENT_GET_PROCESS_STATE();
   uint64_t id;
   uint32_t format, width, height;

   CLIENT_LOCK();
   id = process->inited ? khrn_global_image_map_lookup(&process->global_image_egl_images, (uint32_t)(uintptr_t)image) : 0;
   CLIENT_UNLOCK();
   if (!id) {
      return false;
   }
   global_image_id[0] = (GLuint)id;
   global_image_id[1] = (GLuint)(id >> 32);

   platform_get_global_image_info(global_image_id[0], global_image_id[1], &format, &width, &height);

   if (!(format & ((thread->opengl.context->type == OPENGL_ES_11) ?
      (render ? EGL_PIXEL_FORMAT_RENDER_GLES_BRCM : EGL_PIXEL_FORMAT_GLES_TEXTURE_BRCM) :
      (render ? EGL_PIXEL_FORMAT_RENDER_GLES2_BRCM : EGL_PIXEL_FORMAT_GLES2_TEXTURE_BRCM))) ||
      (width == 0) || (height == 0)) {
      return false;
   }

   /* format and max width/height checks done on server */

   return true;
}