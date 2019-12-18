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
typedef  enum gl_capability_enum { ____Placeholder_gl_capability_enum } gl_capability_enum ;
typedef  int GLint ;

/* Variables and functions */
#define  GL_CAPS_ARGB8 146 
#define  GL_CAPS_BGRA8888 145 
#define  GL_CAPS_DEBUG 144 
#define  GL_CAPS_EGLIMAGE 143 
#define  GL_CAPS_ES2_COMPAT 142 
#define  GL_CAPS_FBO 141 
#define  GL_CAPS_FP_FBO 140 
#define  GL_CAPS_FULL_NPOT_SUPPORT 139 
#define  GL_CAPS_GLES3_SUPPORTED 138 
#define  GL_CAPS_MIPMAP 137 
#define  GL_CAPS_NONE 136 
#define  GL_CAPS_PACKED_DEPTH_STENCIL 135 
#define  GL_CAPS_SRGB_FBO 134 
#define  GL_CAPS_SRGB_FBO_ES3 133 
#define  GL_CAPS_SYNC 132 
#define  GL_CAPS_TEX_STORAGE 131 
#define  GL_CAPS_TEX_STORAGE_EXT 130 
#define  GL_CAPS_UNPACK_ROW_LENGTH 129 
#define  GL_CAPS_VAO 128 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 int /*<<< orphan*/  GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB ; 
 int /*<<< orphan*/  GL_MAX_TEXTURE_SIZE ; 
 int /*<<< orphan*/  GL_RENDERER ; 
 int /*<<< orphan*/  GL_VENDOR ; 
 int /*<<< orphan*/  GL_VERSION ; 
 int /*<<< orphan*/  glBindVertexArray ; 
 int /*<<< orphan*/  glClientWaitSync ; 
 int /*<<< orphan*/  glDeleteSync ; 
 int /*<<< orphan*/  glDeleteVertexArrays ; 
 int /*<<< orphan*/ * glEGLImageTargetTexture2DOES ; 
 int /*<<< orphan*/  glFenceSync ; 
 int /*<<< orphan*/  glGenVertexArrays ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glGetProgramivARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_query_core_context_in_use () ; 
 int gl_query_extension (char*) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

bool gl_check_capability(enum gl_capability_enum enum_idx)
{
   unsigned major       = 0;
   unsigned minor       = 0;
   const char *vendor   = (const char*)glGetString(GL_VENDOR);
   const char *renderer = (const char*)glGetString(GL_RENDERER);
   const char *version  = (const char*)glGetString(GL_VERSION);
#ifdef HAVE_OPENGLES
   if (version && sscanf(version, "OpenGL ES %u.%u", &major, &minor) != 2)
#else
   if (version && sscanf(version, "%u.%u", &major, &minor) != 2)
#endif
      major = minor = 0;

   (void)vendor;
   (void)renderer;

   switch (enum_idx)
   {
      case GL_CAPS_GLES3_SUPPORTED:
#if defined(HAVE_OPENGLES)
         if (major >= 3)
            return true;
#endif
         break;
      case GL_CAPS_EGLIMAGE:
#if defined(HAVE_EGL) && defined(HAVE_OPENGLES)
         if (glEGLImageTargetTexture2DOES != NULL)
            return true;
#endif
         break;
      case GL_CAPS_SYNC:
#ifdef HAVE_OPENGLES
         if (major >= 3)
            return true;
#else
         if (gl_query_extension("ARB_sync") &&
               glFenceSync && glDeleteSync && glClientWaitSync)
            return true;
#endif
         break;
      case GL_CAPS_MIPMAP:
         {
            static bool extension_queried = false;
            static bool extension         = false;

            if (!extension_queried)
            {
               extension         = gl_query_extension("ARB_framebuffer_object");
               extension_queried = true;
            }

            if (extension)
               return true;
         }
         break;
      case GL_CAPS_VAO:
#ifndef HAVE_OPENGLES
         if (!gl_query_core_context_in_use() && !gl_query_extension("ARB_vertex_array_object"))
            return false;

         if (glGenVertexArrays && glBindVertexArray && glDeleteVertexArrays)
            return true;
#endif
         break;
      case GL_CAPS_FBO:
#if defined(HAVE_PSGL) || defined(HAVE_OPENGLES2) || defined(HAVE_OPENGLES3) || defined(HAVE_OPENGLES_3_1) || defined(HAVE_OPENGLES_3_2)
         return true;
#else
         if (     !gl_query_core_context_in_use()
               && !gl_query_extension("ARB_framebuffer_object")
               && !gl_query_extension("EXT_framebuffer_object"))
            return false;

         if (gl_query_extension("ARB_framebuffer_object"))
            return true;

         if (gl_query_extension("EXT_framebuffer_object"))
            return true;

         if (major >= 3)
            return true;
         break;
#endif
      case GL_CAPS_ARGB8:
#ifdef HAVE_OPENGLES
         if (gl_query_extension("OES_rgb8_rgba8")
               || gl_query_extension("ARM_rgba8")
                  || major >= 3)
            return true;
#else
         /* TODO/FIXME - implement this for non-GLES? */
#endif
         break;
      case GL_CAPS_DEBUG:
         if (gl_query_extension("KHR_debug"))
            return true;
#ifndef HAVE_OPENGLES
         if (gl_query_extension("ARB_debug_output"))
            return true;
#endif
         break;
      case GL_CAPS_PACKED_DEPTH_STENCIL:
         if (major >= 3)
            return true;
         if (gl_query_extension("OES_packed_depth_stencil"))
            return true;
         if (gl_query_extension("EXT_packed_depth_stencil"))
            return true;
         break;
      case GL_CAPS_ES2_COMPAT:
#ifndef HAVE_OPENGLES
         /* ATI card detected, skipping check for GL_RGB565 support... */
         if (vendor && renderer && (strstr(vendor, "ATI") || strstr(renderer, "ATI")))
            return false;

         if (gl_query_extension("ARB_ES2_compatibility"))
            return true;
#endif
         break;
      case GL_CAPS_UNPACK_ROW_LENGTH:
#ifdef HAVE_OPENGLES
         if (major >= 3)
            return true;

         /* Extension GL_EXT_unpack_subimage, can copy textures faster
          * than using UNPACK_ROW_LENGTH */
         if (gl_query_extension("GL_EXT_unpack_subimage"))
            return true;
#endif
         break;
      case GL_CAPS_FULL_NPOT_SUPPORT:
         if (major >= 3)
            return true;
#ifdef HAVE_OPENGLES
         if (gl_query_extension("ARB_texture_non_power_of_two") ||
               gl_query_extension("OES_texture_npot"))
            return true;
#else
         {
            GLint max_texture_size = 0;
            GLint max_native_instr = 0;
            /* try to detect actual npot support. might fail for older cards. */
            bool  arb_npot         = gl_query_extension("ARB_texture_non_power_of_two");
            bool  arb_frag_program = gl_query_extension("ARB_fragment_program");

            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);

#ifdef GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB
            if (arb_frag_program && glGetProgramivARB)
               glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB,
                     GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &max_native_instr);
#endif

            if (arb_npot && arb_frag_program &&
                  (max_texture_size >= 8192) && (max_native_instr >= 4096))
               return true;
         }
#endif
         break;
      case GL_CAPS_SRGB_FBO_ES3:
#ifdef HAVE_OPENGLES
         if (major >= 3)
            return true;
#else
         break;
#endif
      case GL_CAPS_SRGB_FBO:
#if defined(HAVE_OPENGLES)
         if (major >= 3 || gl_query_extension("EXT_sRGB"))
            return true;
#endif
         if (gl_check_capability(GL_CAPS_FBO))
         {
            if (   gl_query_core_context_in_use() ||
                  (gl_query_extension("EXT_texture_sRGB")
                   && gl_query_extension("ARB_framebuffer_sRGB"))
               )
               return true;
         }
         break;
      case GL_CAPS_FP_FBO:
         /* GLES - No extensions for float FBO currently. */
#ifndef HAVE_OPENGLES
         if (gl_check_capability(GL_CAPS_FBO))
         {
            /* Float FBO is core in 3.2. */
            if (gl_query_core_context_in_use() || gl_query_extension("ARB_texture_float"))
               return true;
         }
#endif
         break;
      case GL_CAPS_BGRA8888:
#ifdef HAVE_OPENGLES
         /* There are both APPLE and EXT variants. */
         if (gl_query_extension("BGRA8888") && !strstr(renderer, "VideoCore"))
            return true;
#else
         return true;
#endif
         break;
      case GL_CAPS_TEX_STORAGE:
#ifdef HAVE_OPENGLES
         if (major >= 3)
            return true;
#else
         if (vendor && strstr(vendor, "ATI Technologies"))
            return false;
         if (gl_query_extension("ARB_texture_storage"))
            return true;
#endif
         break;
      case GL_CAPS_TEX_STORAGE_EXT:
#ifdef TARGET_OS_IPHONE
           /* Not working on iOS */
           return false;
#else
         if (gl_query_extension("EXT_texture_storage"))
            return true;
#endif
         break;
      case GL_CAPS_NONE:
      default:
         break;
   }

   return false;
}