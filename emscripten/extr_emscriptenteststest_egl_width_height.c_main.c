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
typedef  int EGLint ;
typedef  int /*<<< orphan*/  EGLSurface ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;
typedef  int /*<<< orphan*/  EGLDisplay ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 int EGL_BLUE_SIZE ; 
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
 int EGL_GREEN_SIZE ; 
 int /*<<< orphan*/  EGL_HEIGHT ; 
 int EGL_NONE ; 
 int EGL_RED_SIZE ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 int /*<<< orphan*/  eglChooseConfig (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglGetConfigs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  eglGetDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglInitialize (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  eglQuerySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int main(int argc, char *argv[])
{
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    EGLint major, minor;
    eglInitialize(display, &major, &minor);

    EGLint numConfigs;
    eglGetConfigs(display, NULL, 0, &numConfigs);

    EGLint attribs[] = {
        EGL_RED_SIZE, 5,
        EGL_GREEN_SIZE, 6,
        EGL_BLUE_SIZE, 5,
        EGL_NONE
    };
    EGLConfig config;
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    EGLNativeWindowType dummyWindow;
    EGLSurface surface = eglCreateWindowSurface(display, config, dummyWindow, NULL);

    EGLint width, height;
    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);

    printf("(%d, %d)\n", width, height);

#ifdef REPORT_RESULT
    int result = 0;
    if(width == 300 && height == 150)
    {
        result = 1;
    }
    REPORT_RESULT(result);
#endif
}