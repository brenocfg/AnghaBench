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
typedef  scalar_t__ GLenum ;
typedef  int /*<<< orphan*/  GLContext ;

/* Variables and functions */
 scalar_t__ CreateContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyContext (int /*<<< orphan*/ *) ; 
 scalar_t__ GLEW_OK ; 
 int /*<<< orphan*/  GLU_EXTENSIONS ; 
 int /*<<< orphan*/  GLU_VERSION ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_RENDERER ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  GL_VENDOR ; 
 int /*<<< orphan*/  GL_VERSION ; 
 int /*<<< orphan*/  InitContext (int /*<<< orphan*/ *) ; 
 scalar_t__ ParseArgs (int,char**) ; 
 int /*<<< orphan*/  PrintExtensions (char*) ; 
 int /*<<< orphan*/  VisualInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 char* glGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXGetCurrentDisplay () ; 
 char* glXQueryExtensionsString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ glewExperimental ; 
 char* glewGetErrorString (scalar_t__) ; 
 scalar_t__ glewInit () ; 
 char* gluGetString (int /*<<< orphan*/ ) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 

int 
main (int argc, char** argv)
{
  GLenum err;
  GLContext ctx;

  /* ---------------------------------------------------------------------- */
  /* parse arguments */
  if (GL_TRUE == ParseArgs(argc-1, argv+1))
  {
#if defined(_WIN32)
    fprintf(stderr, "Usage: visualinfo [-a] [-s] [-h] [-pf <id>]\n");
    fprintf(stderr, "        -a: show all visuals\n");
    fprintf(stderr, "        -s: display to stdout instead of visualinfo.txt\n");
    fprintf(stderr, "        -pf <id>: use given pixelformat\n");
    fprintf(stderr, "        -h: this screen\n");
#else
    fprintf(stderr, "Usage: visualinfo [-h] [-display <display>] [-visual <id>]\n");
    fprintf(stderr, "        -h: this screen\n");
    fprintf(stderr, "        -display <display>: use given display\n");
    fprintf(stderr, "        -visual <id>: use given visual\n");
#endif
    return 1;
  }

  /* ---------------------------------------------------------------------- */
  /* create OpenGL rendering context */
  InitContext(&ctx);
  if (GL_TRUE == CreateContext(&ctx))
  {
    fprintf(stderr, "Error: CreateContext failed\n");
    DestroyContext(&ctx);
    return 1;
  }

  /* ---------------------------------------------------------------------- */
  /* initialize GLEW */
  glewExperimental = GL_TRUE;
#ifdef GLEW_MX
  err = glewContextInit(glewGetContext());
#  ifdef _WIN32
  err = err || wglewContextInit(wglewGetContext());
#  elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
  err = err || glxewContextInit(glxewGetContext());
#  endif
#else
  err = glewInit();
#endif
  if (GLEW_OK != err)
  {
    fprintf(stderr, "Error [main]: glewInit failed: %s\n", glewGetErrorString(err));
    DestroyContext(&ctx);
    return 1;
  }

  /* ---------------------------------------------------------------------- */
  /* open file */
#if defined(_WIN32)
  if (!displaystdout) 
    file = fopen("visualinfo.txt", "w");
  if (file == NULL)
    file = stdout;
#else
  file = stdout;
#endif

  /* ---------------------------------------------------------------------- */
  /* output header information */
  /* OpenGL extensions */
  fprintf(file, "OpenGL vendor string: %s\n", glGetString(GL_VENDOR));
  fprintf(file, "OpenGL renderer string: %s\n", glGetString(GL_RENDERER));
  fprintf(file, "OpenGL version string: %s\n", glGetString(GL_VERSION));
  fprintf(file, "OpenGL extensions (GL_): \n");
  PrintExtensions((char*)glGetString(GL_EXTENSIONS));

#ifndef GLEW_NO_GLU
  /* GLU extensions */
  fprintf(file, "GLU version string: %s\n", gluGetString(GLU_VERSION));
  fprintf(file, "GLU extensions (GLU_): \n");
  PrintExtensions((char*)gluGetString(GLU_EXTENSIONS));
#endif

  /* ---------------------------------------------------------------------- */
  /* extensions string */
#if defined(_WIN32)
  /* WGL extensions */
  if (WGLEW_ARB_extensions_string || WGLEW_EXT_extensions_string)
  {
    fprintf(file, "WGL extensions (WGL_): \n");
    PrintExtensions(wglGetExtensionsStringARB ? 
                    (char*)wglGetExtensionsStringARB(ctx.dc) :
		    (char*)wglGetExtensionsStringEXT());
  }
#elif defined(__APPLE__) && !defined(GLEW_APPLE_GLX)
  
#else
  /* GLX extensions */
  fprintf(file, "GLX extensions (GLX_): \n");
  PrintExtensions(glXQueryExtensionsString(glXGetCurrentDisplay(), 
                                           DefaultScreen(glXGetCurrentDisplay())));
#endif

  /* ---------------------------------------------------------------------- */
  /* enumerate all the formats */
  VisualInfo(&ctx);

  /* ---------------------------------------------------------------------- */
  /* release resources */
  DestroyContext(&ctx);
  if (file != stdout)
    fclose(file);
  return 0;
}