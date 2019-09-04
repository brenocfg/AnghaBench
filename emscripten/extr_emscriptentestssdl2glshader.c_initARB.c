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
typedef  scalar_t__ PFNGLUSEPROGRAMOBJECTARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM4FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM4FARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM3FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM3FARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM2FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM2FARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM1IARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM1FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM1FARBPROC ;
typedef  scalar_t__ PFNGLSHADERSOURCEARBPROC ;
typedef  scalar_t__ PFNGLLINKPROGRAMARBPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMLOCATIONARBPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPARAMETERIVARBPROC ;
typedef  scalar_t__ PFNGLGETINFOLOGARBPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMARBPROC ;
typedef  scalar_t__ PFNGLDELETEOBJECTARBPROC ;
typedef  scalar_t__ PFNGLCREATESHADEROBJECTARBPROC ;
typedef  scalar_t__ PFNGLCREATEPROGRAMOBJECTARBPROC ;
typedef  scalar_t__ PFNGLCOMPILESHADERARBPROC ;
typedef  scalar_t__ PFNGLBINDATTRIBLOCATIONARBPROC ;
typedef  scalar_t__ PFNGLATTACHOBJECTARBPROC ;

/* Variables and functions */
 scalar_t__ SDL_GL_GetProcAddress (char*) ; 
 scalar_t__ glAttachObject_ ; 
 scalar_t__ glBindAttribLocation_ ; 
 scalar_t__ glCompileShader_ ; 
 scalar_t__ glCreateProgramObject_ ; 
 scalar_t__ glCreateShaderObject_ ; 
 scalar_t__ glDeleteObject_ ; 
 scalar_t__ glGetActiveUniform_ ; 
 scalar_t__ glGetInfoLog_ ; 
 scalar_t__ glGetObjectParameteriv_ ; 
 scalar_t__ glGetUniformLocation_ ; 
 scalar_t__ glLinkProgram_ ; 
 scalar_t__ glShaderSource_ ; 
 scalar_t__ glUniform1f_ ; 
 scalar_t__ glUniform1fv_ ; 
 scalar_t__ glUniform1i_ ; 
 scalar_t__ glUniform2f_ ; 
 scalar_t__ glUniform2fv_ ; 
 scalar_t__ glUniform3f_ ; 
 scalar_t__ glUniform3fv_ ; 
 scalar_t__ glUniform4f_ ; 
 scalar_t__ glUniform4fv_ ; 
 scalar_t__ glUseProgramObject_ ; 

void initARB() {
  glCreateProgramObject_ =        (PFNGLCREATEPROGRAMOBJECTARBPROC)     SDL_GL_GetProcAddress("glCreateProgramObjectARB");
  glDeleteObject_ =               (PFNGLDELETEOBJECTARBPROC)            SDL_GL_GetProcAddress("glDeleteObjectARB");
  glUseProgramObject_ =           (PFNGLUSEPROGRAMOBJECTARBPROC)        SDL_GL_GetProcAddress("glUseProgramObjectARB");
  glCreateShaderObject_ =         (PFNGLCREATESHADEROBJECTARBPROC)      SDL_GL_GetProcAddress("glCreateShaderObjectARB");
  glShaderSource_ =               (PFNGLSHADERSOURCEARBPROC)            SDL_GL_GetProcAddress("glShaderSourceARB");
  glCompileShader_ =              (PFNGLCOMPILESHADERARBPROC)           SDL_GL_GetProcAddress("glCompileShaderARB");
  glGetObjectParameteriv_ =       (PFNGLGETOBJECTPARAMETERIVARBPROC)    SDL_GL_GetProcAddress("glGetObjectParameterivARB");
  glAttachObject_ =               (PFNGLATTACHOBJECTARBPROC)            SDL_GL_GetProcAddress("glAttachObjectARB");
  glGetInfoLog_ =                 (PFNGLGETINFOLOGARBPROC)              SDL_GL_GetProcAddress("glGetInfoLogARB");
  glLinkProgram_ =                (PFNGLLINKPROGRAMARBPROC)             SDL_GL_GetProcAddress("glLinkProgramARB");
  glGetUniformLocation_ =         (PFNGLGETUNIFORMLOCATIONARBPROC)      SDL_GL_GetProcAddress("glGetUniformLocationARB");
  glUniform1f_ =                  (PFNGLUNIFORM1FARBPROC)               SDL_GL_GetProcAddress("glUniform1fARB");
  glUniform2f_ =                  (PFNGLUNIFORM2FARBPROC)               SDL_GL_GetProcAddress("glUniform2fARB");
  glUniform3f_ =                  (PFNGLUNIFORM3FARBPROC)               SDL_GL_GetProcAddress("glUniform3fARB");
  glUniform4f_ =                  (PFNGLUNIFORM4FARBPROC)               SDL_GL_GetProcAddress("glUniform4fARB");
  glUniform1fv_ =                 (PFNGLUNIFORM1FVARBPROC)              SDL_GL_GetProcAddress("glUniform1fvARB");
  glUniform2fv_ =                 (PFNGLUNIFORM2FVARBPROC)              SDL_GL_GetProcAddress("glUniform2fvARB");
  glUniform3fv_ =                 (PFNGLUNIFORM3FVARBPROC)              SDL_GL_GetProcAddress("glUniform3fvARB");
  glUniform4fv_ =                 (PFNGLUNIFORM4FVARBPROC)              SDL_GL_GetProcAddress("glUniform4fvARB");
  glUniform1i_ =                  (PFNGLUNIFORM1IARBPROC)               SDL_GL_GetProcAddress("glUniform1iARB");
  glBindAttribLocation_ =         (PFNGLBINDATTRIBLOCATIONARBPROC)      SDL_GL_GetProcAddress("glBindAttribLocationARB");
  glGetActiveUniform_ =           (PFNGLGETACTIVEUNIFORMARBPROC)        SDL_GL_GetProcAddress("glGetActiveUniformARB");
}