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
typedef  int /*<<< orphan*/  TEAPOT_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GL_AMBIENT ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_LIGHT0 ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glClearDepthf (double) ; 
 int /*<<< orphan*/  glDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLightfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 

__attribute__((used)) static void init_ogl(TEAPOT_STATE_T *state)
{
   // Set background color and clear buffers
   glClearColor((0.3922f+7*0.5f)/8, (0.1176f+7*0.5f)/8, (0.5882f+7*0.5f)/8, 1.0f);

   // Enable back face culling.
   glEnable(GL_CULL_FACE);

   glEnable(GL_DEPTH_TEST);
   glClearDepthf(1.0);
   glDepthFunc(GL_LEQUAL);

   float noAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
   glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHTING);
}