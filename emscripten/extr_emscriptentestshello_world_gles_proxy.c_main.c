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
 int /*<<< orphan*/  gears_draw ; 
 int /*<<< orphan*/  gears_idle ; 
 int /*<<< orphan*/  gears_init () ; 
 int /*<<< orphan*/  gears_reshape ; 
 int /*<<< orphan*/  gears_special ; 
 int /*<<< orphan*/  glutCreateWindow (char*) ; 
 int /*<<< orphan*/  glutDisplayFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutIdleFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutInit (int*,char**) ; 
 int /*<<< orphan*/  glutInitDisplayMode (int) ; 
 int /*<<< orphan*/  glutInitWindowSize (int,int) ; 
 int /*<<< orphan*/  glutMainLoop () ; 
 int /*<<< orphan*/  glutReshapeFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutSpecialFunc (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
#ifdef __EMSCRIPTEN__
   // Don't trigger the reftest immediately after main finishes,
   // this test uses rAF to perform rendering, so let it trigger
   // the reftest after having rendered some frames.
   EM_ASM(Module['postRun'] = undefined);
#endif

   /* Initialize the window */
   glutInit(&argc, argv);
   glutInitWindowSize(300, 300);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutCreateWindow("es2gears");

   /* Set up glut callback functions */
   glutIdleFunc (gears_idle);
   glutReshapeFunc(gears_reshape);
   glutDisplayFunc(gears_draw);
   glutSpecialFunc(gears_special);

   /* Initialize the gears */
   gears_init();

   glutMainLoop();

   return 0;
}