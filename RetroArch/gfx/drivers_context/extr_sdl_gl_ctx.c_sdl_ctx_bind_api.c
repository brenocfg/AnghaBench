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
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;

/* Variables and functions */
 int GFX_CTX_OPENGL_API ; 
 int GFX_CTX_OPENGL_ES_API ; 
 int /*<<< orphan*/  SDL_GL_CONTEXT_MAJOR_VERSION ; 
 int /*<<< orphan*/  SDL_GL_CONTEXT_MINOR_VERSION ; 
 unsigned int SDL_GL_CONTEXT_PROFILE_COMPATIBILITY ; 
 unsigned int SDL_GL_CONTEXT_PROFILE_ES ; 
 int /*<<< orphan*/  SDL_GL_CONTEXT_PROFILE_MASK ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int g_major ; 
 unsigned int g_minor ; 
 int sdl_api ; 

__attribute__((used)) static bool sdl_ctx_bind_api(void *data,
      enum gfx_ctx_api api, unsigned major,
      unsigned minor)
{
#ifdef HAVE_SDL2
   unsigned profile;

   if (api != GFX_CTX_OPENGL_API && api != GFX_CTX_OPENGL_ES_API)
      return false;

   profile = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;

   if (api == GFX_CTX_OPENGL_ES_API)
      profile = SDL_GL_CONTEXT_PROFILE_ES;

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
#endif

   sdl_api = api;
   g_major = major;
   g_minor = minor;

#ifndef HAVE_SDL2
   if (api != GFX_CTX_OPENGL_API)
      return false;
#endif
   return true;
}