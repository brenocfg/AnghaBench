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
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glColor3f (float,float,float) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glRotatef (float,float,float,float) ; 
 int /*<<< orphan*/  glTranslatef (float,float,float) ; 
 int /*<<< orphan*/  glVertex3f (float,float,float) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glfwGetMousePos (int*,int /*<<< orphan*/ *) ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwGetWindowSize (int*,int*) ; 
 int /*<<< orphan*/  glfwSwapBuffers () ; 
 int /*<<< orphan*/  gluLookAt (float,float,float,float,float,float,float,float,float) ; 
 int /*<<< orphan*/  gluPerspective (float,float,float,float) ; 

void Draw(void)
{
  int width, height, x;
  double t;

  t = glfwGetTime ();
  glfwGetMousePos (&x, NULL);

  // Get window size (may be different than the requested size)
  glfwGetWindowSize (&width, &height);

  // Special case: avoid division by zero below
  height = height > 0 ? height : 1;

  glViewport (0, 0, width, height);
  // Clear color buffer to black
  glClearColor (0.1f, 0.2f, 0.3f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);

  // Select and setup the projection matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (65.0f, (GLfloat) width / (GLfloat) height, 1.0f, 100.0f);

  // Select and setup the modelview matrix
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  gluLookAt (0.0f, 1.0f, 0.0f,	// Eye-position
	     0.0f, 20.0f, 0.0f,	// View-point
	     0.0f, 0.0f, 1.0f);	// Up-vector

  // Draw a rotating colorful triangle
  //glTranslatef (0.0f, 14.0f, 0.0f);
  glTranslatef (0.0f, 1.0f, 0.0f);
  glRotatef (0.3f * (GLfloat) x + (GLfloat) t * 100.0f, 0.0f, 0.0f, 1.0f);
  glBegin (GL_TRIANGLES);
  glColor3f (1.0f, 0.0f, 0.0f);
  glVertex3f (-5.0f, 0.0f, -4.0f);
  glColor3f (0.0f, 1.0f, 0.0f);
  glVertex3f (5.0f, 0.0f, -4.0f);
  glColor3f (0.0f, 0.0f, 1.0f);
  glVertex3f (0.0f, 0.0f, 6.0f);
  glEnd ();

  // Swap buffers
  glfwSwapBuffers ();
}