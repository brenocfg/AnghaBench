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
 int GLUT_DEPTH ; 
 int GLUT_DOUBLE ; 
 int GLUT_RGB ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  SDL_GL_GetProcAddress (char*) ; 
 int /*<<< orphan*/  gears_draw () ; 
 int /*<<< orphan*/  gears_idle () ; 
 int /*<<< orphan*/  gears_init () ; 
 int /*<<< orphan*/  glutCreateWindow (char*) ; 
 int /*<<< orphan*/  glutInit (int*,char**) ; 
 int /*<<< orphan*/  glutInitDisplayMode (int) ; 
 int /*<<< orphan*/  glutInitWindowSize (int,int) ; 

int
main(int argc, char *argv[])
{
   if (argc == 12) SDL_GL_GetProcAddress("glWhatevah");

   /* Initialize the window */
   glutInit(&argc, argv);
   glutInitWindowSize(300, 300);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutCreateWindow("es2gears");

   gears_idle();
   gears_init();
   gears_draw();

   REPORT_RESULT(1);

   return 0;
}