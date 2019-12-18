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
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ EGLint ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;
typedef  int /*<<< orphan*/  EGLNativeDisplayType ;
typedef  int /*<<< orphan*/ * EGLConfig ;

/* Variables and functions */
 scalar_t__ EGL_NONE ; 
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_CW ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT_5_6_5 ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 void* calloc (int,int) ; 
 scalar_t__ ectxt ; 
 scalar_t__ edpy ; 
 int /*<<< orphan*/  eglChooseConfig (scalar_t__,scalar_t__*,int /*<<< orphan*/ **,int,scalar_t__*) ; 
 scalar_t__ eglCreateContext (scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ eglCreateWindowSurface (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ eglGetDisplay (int /*<<< orphan*/ ) ; 
 int eglGetError () ; 
 int /*<<< orphan*/  eglInitialize (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ esfc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFrontFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  glTexParameterf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gl_es_display ; 
 void* gl_es_surface ; 
 scalar_t__ gl_have_error (char*) ; 
 int gl_platform_init (void**,void**,int*) ; 
 int /*<<< orphan*/  stderr ; 

int gl_init(void *display, void *window, int *quirks)
{
	EGLConfig ecfg = NULL;
	GLuint texture_name = 0;
	void *tmp_texture_mem = NULL;
	EGLint num_config;
	int retval = -1;
	int ret;
	EGLint attr[] =
	{
		EGL_NONE
	};

	ret = gl_platform_init(&display, &window, quirks);
	if (ret != 0) {
		fprintf(stderr, "gl_platform_init failed with %d\n", ret);
		goto out;
	}

	tmp_texture_mem = calloc(1, 1024 * 512 * 2);
	if (tmp_texture_mem == NULL) {
		fprintf(stderr, "OOM\n");
		goto out;
	}

	edpy = eglGetDisplay((EGLNativeDisplayType)display);
	if (edpy == EGL_NO_DISPLAY) {
		fprintf(stderr, "Failed to get EGL display\n");
		goto out;
	}

	if (!eglInitialize(edpy, NULL, NULL)) {
		fprintf(stderr, "Failed to initialize EGL\n");
		goto out;
	}

	if (!eglChooseConfig(edpy, attr, &ecfg, 1, &num_config)) {
		fprintf(stderr, "Failed to choose config (%x)\n", eglGetError());
		goto out;
	}

	if (ecfg == NULL || num_config == 0) {
		fprintf(stderr, "No EGL configs available\n");
		goto out;
	}

	esfc = eglCreateWindowSurface(edpy, ecfg,
		(EGLNativeWindowType)window, NULL);
	if (esfc == EGL_NO_SURFACE) {
		fprintf(stderr, "Unable to create EGL surface (%x)\n",
			eglGetError());
		goto out;
	}

	ectxt = eglCreateContext(edpy, ecfg, EGL_NO_CONTEXT, NULL);
	if (ectxt == EGL_NO_CONTEXT) {
		fprintf(stderr, "Unable to create EGL context (%x)\n",
			eglGetError());
		goto out;
	}

	eglMakeCurrent(edpy, esfc, esfc, ectxt);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture_name);

	glBindTexture(GL_TEXTURE_2D, texture_name);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 512, 0, GL_RGB,
		GL_UNSIGNED_SHORT_5_6_5, tmp_texture_mem);
	if (gl_have_error("glTexImage2D"))
		goto out;

	// no mipmaps
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glViewport(0, 0, 512, 512);
	glLoadIdentity();
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	if (gl_have_error("init"))
		goto out;

	gl_es_display = (void *)edpy;
	gl_es_surface = (void *)esfc;
	retval = 0;
out:
	free(tmp_texture_mem);
	return retval;
}