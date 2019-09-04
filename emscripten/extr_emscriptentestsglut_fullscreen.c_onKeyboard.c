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

/* Variables and functions */
 int /*<<< orphan*/  GLUT_INIT_WINDOW_HEIGHT ; 
 int /*<<< orphan*/  GLUT_INIT_WINDOW_WIDTH ; 
 int fullscreen ; 
 int /*<<< orphan*/  glutFullScreen () ; 
 int /*<<< orphan*/  glutGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutReshapeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

void onKeyboard(unsigned char key, int x, int y)
{
  if (key == 'f') {
#ifdef __EMSCRIPTEN__
    EmscriptenFullscreenChangeEvent fullscreen_status;
    int fullscreen;
    emscripten_get_fullscreen_status(&fullscreen_status);
    fullscreen = fullscreen_status.isFullscreen;
#endif
    if (fullscreen) {
      glutReshapeWindow(glutGet(GLUT_INIT_WINDOW_WIDTH), glutGet(GLUT_INIT_WINDOW_HEIGHT));
    } else {
      glutFullScreen();
    }
#ifndef __EMSCRIPTEN__
    fullscreen = !fullscreen;
#endif
    trace("onKeyboard");
  }
}