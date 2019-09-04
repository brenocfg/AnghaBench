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
typedef  double GLfloat ;

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int M_PI ; 
 int angle ; 
 int /*<<< orphan*/  draw_gear (int /*<<< orphan*/ ,double*,double,double,int,double const*) ; 
 int /*<<< orphan*/  gear1 ; 
 int /*<<< orphan*/  gear2 ; 
 int /*<<< orphan*/  gear3 ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 
 int /*<<< orphan*/  glutSwapBuffers () ; 
 int /*<<< orphan*/  identity (double*) ; 
 int /*<<< orphan*/  rotate (double*,int,int,int,int) ; 
 int /*<<< orphan*/  translate (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* view_rot ; 

__attribute__((used)) static void
gears_draw(void)
{
   const static GLfloat red[4] = { 0.8, 0.1, 0.0, 1.0 };
   const static GLfloat green[4] = { 0.0, 0.8, 0.2, 1.0 };
   const static GLfloat blue[4] = { 0.2, 0.2, 1.0, 1.0 };
   GLfloat transform[16];
   identity(transform);

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   /* Translate and rotate the view */
   translate(transform, 0, 0, -20);
   rotate(transform, 2 * M_PI * view_rot[0] / 360.0, 1, 0, 0);
   rotate(transform, 2 * M_PI * view_rot[1] / 360.0, 0, 1, 0);
   rotate(transform, 2 * M_PI * view_rot[2] / 360.0, 0, 0, 1);

   /* Draw the gears */
   draw_gear(gear1, transform, -3.0, -2.0, angle, red);
   draw_gear(gear2, transform, 3.1, -2.0, -2 * angle - 9.0, green);
   draw_gear(gear3, transform, -3.1, 4.2, -2 * angle - 25.0, blue);

   glutSwapBuffers();

#ifdef LONGTEST
   glutPostRedisplay(); // check for issues with not throttling calls
#endif
}