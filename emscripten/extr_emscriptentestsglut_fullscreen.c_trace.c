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
typedef  int /*<<< orphan*/  time_t ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_SCREEN_HEIGHT ; 
 int /*<<< orphan*/  GLUT_SCREEN_WIDTH ; 
 int /*<<< orphan*/  GLUT_WINDOW_HEIGHT ; 
 int /*<<< orphan*/  GLUT_WINDOW_WIDTH ; 
 int /*<<< orphan*/  GL_VIEWPORT ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 int glutGet (int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void trace(char* tag)
{
  static char* prev_tag = NULL;
  static int prev_screen_width;
  static int prev_screen_height;
  static int prev_window_width;
  static int prev_window_height;
  static int prev_viewport_width;
  static int prev_viewport_height;
  static int prev_is_fullscreen;
  static int prev_is_resized;
  static int prev_coalesced;
  int screen_width;
  int screen_height;
  int window_width;
  int window_height;
  int viewport_width;
  int viewport_height;
  int is_fullscreen;
  int is_resized;
  int coalesced;

  GLint viewport[4];
  screen_width = glutGet(GLUT_SCREEN_WIDTH);
  screen_height = glutGet(GLUT_SCREEN_HEIGHT);
  window_width = glutGet(GLUT_WINDOW_WIDTH);
  window_height = glutGet(GLUT_WINDOW_HEIGHT);
  glGetIntegerv(GL_VIEWPORT, viewport);
  viewport_width = viewport[2];
  viewport_height = viewport[3];
#ifdef __EMSCRIPTEN__
  EmscriptenFullscreenChangeEvent fullscreen_status;
  emscripten_get_fullscreen_status(&fullscreen_status);
  is_fullscreen = fullscreen_status.isFullscreen;
  is_fullscreen = is_fullscreen ? 1 : -1;
  is_resized = EM_ASM_INT({
    return document.getElementById('resize').checked;
  });
  is_resized = is_resized ? 1 : -1;
#else
  is_fullscreen = 0;
  is_resized = 1;
#endif
  coalesced = prev_tag &&
              !strcmp(tag, prev_tag) &&
              screen_width == prev_screen_width &&
              screen_height == prev_screen_height &&
              window_width == prev_window_width &&
              window_height == prev_window_height &&
              viewport_width == prev_viewport_width &&
              viewport_height == prev_viewport_height &&
              is_fullscreen == prev_is_fullscreen &&
              is_resized == prev_is_resized;

  if (coalesced) {
    if (!prev_coalesced) {
      printf("...\n");
    }
  } else {
    time_t t = time(NULL);
    char* local_time = ctime(&t);
    char* message = malloc(strlen(local_time) + strlen(tag) + 500);
    sprintf(message, "[");
    sprintf(message + strlen(message), "%s", local_time);
    sprintf(message + strlen(message) - 1, " ");
    sprintf(message + strlen(message), "%s", tag);
    sprintf(message + strlen(message), "]");
    sprintf(message + strlen(message), " ");
    sprintf(message + strlen(message),
            "screen width: %d"
            ", "
            "screen height: %d"
            ", "
            "window width: %d"
            ", "
            "window height: %d"
            ", "
            "viewport width: %d"
            ", "
            "viewport height: %d"
            ", "
            "fullscreen: %s"
            ", "
            "resize: %s",
            screen_width,
            screen_height,
            window_width,
            window_height,
            viewport_width,
            viewport_height,
            is_fullscreen > 0 ? "yes" : (is_fullscreen < 0 ? "no" : "unknown"),
            is_resized > 0 ? "yes" : (is_resized < 0 ? "no" : "unknown"));
    printf("%s\n", message);
    free(message);
  }

  prev_tag = tag;
  prev_screen_width = screen_width;
  prev_screen_height = screen_height;
  prev_window_width = window_width;
  prev_window_height = window_height;
  prev_viewport_width = viewport_width;
  prev_viewport_height = viewport_height;
  prev_is_fullscreen = is_fullscreen;
  prev_is_resized = is_resized;
  prev_coalesced = coalesced;
}