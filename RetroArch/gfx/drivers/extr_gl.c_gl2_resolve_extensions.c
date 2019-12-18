#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_info_t ;
struct string_list {size_t size; TYPE_2__* elems; } ;
struct TYPE_8__ {scalar_t__ video_hard_sync; } ;
struct TYPE_10__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_11__ {scalar_t__ core_context_in_use; scalar_t__ renderchain_data; void* have_sync; void* support_unpack_row_length; void* have_es2_compat; void* have_mipmap; void* have_full_npot_support; } ;
typedef  TYPE_4__ gl_t ;
typedef  int /*<<< orphan*/  gl2_renderchain_data_t ;
struct TYPE_9__ {char const* data; } ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CAPS_BGRA8888 ; 
 int /*<<< orphan*/  GL_CAPS_ES2_COMPAT ; 
 int /*<<< orphan*/  GL_CAPS_FULL_NPOT_SUPPORT ; 
 int /*<<< orphan*/  GL_CAPS_MIPMAP ; 
 int /*<<< orphan*/  GL_CAPS_SYNC ; 
 int /*<<< orphan*/  GL_CAPS_UNPACK_ROW_LENGTH ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_NUM_EXTENSIONS ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  gl2_renderchain_resolve_extensions (TYPE_4__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 
 scalar_t__ glGetStringi (int /*<<< orphan*/ ,scalar_t__) ; 
 void* gl_check_capability (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char const*,char*) ; 
 int /*<<< orphan*/  video_driver_set_rgba () ; 
 int /*<<< orphan*/  video_driver_unset_rgba () ; 

__attribute__((used)) static bool gl2_resolve_extensions(gl_t *gl, const char *context_ident, const video_info_t *video)
{
   settings_t *settings          = config_get_ptr();

   /* have_es2_compat - GL_RGB565 internal format support.
    * Even though ES2 support is claimed, the format
    * is not supported on older ATI catalyst drivers.
    *
    * The speed gain from using GL_RGB565 is worth
    * adding some workarounds for.
    *
    * have_sync       - Use ARB_sync to reduce latency.
    */
   gl->have_full_npot_support    = gl_check_capability(GL_CAPS_FULL_NPOT_SUPPORT);
   gl->have_mipmap               = gl_check_capability(GL_CAPS_MIPMAP);
   gl->have_es2_compat           = gl_check_capability(GL_CAPS_ES2_COMPAT);
   gl->support_unpack_row_length = gl_check_capability(GL_CAPS_UNPACK_ROW_LENGTH);
   gl->have_sync                 = gl_check_capability(GL_CAPS_SYNC);

   if (gl->have_sync && settings->bools.video_hard_sync)
      RARCH_LOG("[GL]: Using ARB_sync to reduce latency.\n");

   video_driver_unset_rgba();

   gl2_renderchain_resolve_extensions(gl,
         (gl2_renderchain_data_t*)gl->renderchain_data,
         context_ident, video);

#if defined(HAVE_OPENGLES) && !defined(HAVE_PSGL)
   if (!gl_check_capability(GL_CAPS_BGRA8888))
   {
      video_driver_set_rgba();
      RARCH_WARN("[GL]: GLES implementation does not have BGRA8888 extension.\n"
                 "32-bit path will require conversion.\n");
   }
   /* TODO/FIXME - No extensions for float FBO currently. */
#endif

#ifdef GL_DEBUG
   /* Useful for debugging, but kinda obnoxious otherwise. */
   RARCH_LOG("[GL]: Supported extensions:\n");

   if (gl->core_context_in_use)
   {
#ifdef GL_NUM_EXTENSIONS
      GLint exts = 0;
      glGetIntegerv(GL_NUM_EXTENSIONS, &exts);
      for (GLint i = 0; i < exts; i++)
      {
         const char *ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
         if (ext)
            RARCH_LOG("\t%s\n", ext);
      }
#endif
   }
   else
   {
      const char *ext = (const char*)glGetString(GL_EXTENSIONS);

      if (ext)
      {
         size_t i;
         struct string_list *list = string_split(ext, " ");

         for (i = 0; i < list->size; i++)
            RARCH_LOG("\t%s\n", list->elems[i].data);
         string_list_free(list);
      }
   }
#endif

   return true;
}