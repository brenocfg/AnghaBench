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
 unsigned int GLUT_DOUBLE ; 
 unsigned int GLUT_RGBA ; 
 int /*<<< orphan*/  GLUT_WINDOW_ALPHA_SIZE ; 
 int /*<<< orphan*/  GLUT_WINDOW_DEPTH_SIZE ; 
 int /*<<< orphan*/  GLUT_WINDOW_NUM_SAMPLES ; 
 int /*<<< orphan*/  GLUT_WINDOW_STENCIL_SIZE ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutCreateWindow (char*) ; 
 scalar_t__ glutGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutInit (int*,char**) ; 
 int /*<<< orphan*/  glutInitDisplayMode (unsigned int) ; 
 int /*<<< orphan*/  glutInitWindowSize (int,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

int main(int argc, char* argv[]) {
  bool stencilActivated = false;
  bool depthActivated = false;
  bool alphaActivated = false;
  bool antiAliasingActivated = false;

  unsigned int mode = GLUT_RGBA | GLUT_DOUBLE;

#ifdef STENCIL_ACTIVATED
    stencilActivated = true;
    mode |= GLUT_STENCIL;
#endif
#ifdef DEPTH_ACTIVATED
    depthActivated = true;
    mode |= GLUT_DEPTH;
#endif
#ifdef ALPHA_ACTIVATED
    alphaActivated = true;
    mode |= GLUT_ALPHA;
#endif
#ifdef AA_ACTIVATED
    antiAliasingActivated = true;
    mode |= GLUT_MULTISAMPLE;
#endif

  glutInit(&argc, argv);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(mode);
  glutCreateWindow(__FILE__);

  printf("stencil:   %d\n", glutGet(GLUT_WINDOW_STENCIL_SIZE));
  printf("depth:     %d\n", glutGet(GLUT_WINDOW_DEPTH_SIZE));
  printf("alpha:     %d\n", glutGet(GLUT_WINDOW_ALPHA_SIZE));
  printf("antialias: %d\n", glutGet(GLUT_WINDOW_NUM_SAMPLES));
  int result = (
    (!stencilActivated      || glutGet(GLUT_WINDOW_STENCIL_SIZE) > 0) &&
    (!depthActivated        || glutGet(GLUT_WINDOW_DEPTH_SIZE)   > 0) &&
    (!alphaActivated        || glutGet(GLUT_WINDOW_ALPHA_SIZE)   > 0) &&
    (!antiAliasingActivated || glutGet(GLUT_WINDOW_NUM_SAMPLES)  > 0)
    );

  // fix-up "ReferenceError: GL is not defined,createContext" due to
  // overzealous JS stripping
  glClear(0);

  REPORT_RESULT(result);
}