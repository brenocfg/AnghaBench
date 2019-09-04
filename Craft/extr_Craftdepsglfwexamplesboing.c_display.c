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
 int /*<<< orphan*/  DRAW_BALL ; 
 int /*<<< orphan*/  DRAW_BALL_SHADOW ; 
 int /*<<< orphan*/  DrawBoingBall () ; 
 int /*<<< orphan*/  DrawGrid () ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  drawBallHow ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glFlush () ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 

void display(void)
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glPushMatrix();

   drawBallHow = DRAW_BALL_SHADOW;
   DrawBoingBall();

   DrawGrid();

   drawBallHow = DRAW_BALL;
   DrawBoingBall();

   glPopMatrix();
   glFlush();
}