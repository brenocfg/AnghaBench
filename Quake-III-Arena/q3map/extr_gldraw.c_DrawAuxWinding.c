#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numpoints; int /*<<< orphan*/ ** p; } ;
typedef  TYPE_1__ winding_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_LINE_LOOP ; 
 int /*<<< orphan*/  GL_POLYGON ; 
 int /*<<< orphan*/  drawflag ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor4f (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glFlush () ; 
 int /*<<< orphan*/  glVertex3f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void DrawAuxWinding (winding_t *w)
{
	int		i;

	if (!drawflag)
		return;

	glColor4f (0,0,0,0.5);
	glBegin (GL_LINE_LOOP);
	for (i=0 ; i<w->numpoints ; i++)
		glVertex3f (w->p[i][0],w->p[i][1],w->p[i][2] );
	glEnd ();

	glColor4f (1,0,0,0.3);
	glBegin (GL_POLYGON);
	for (i=0 ; i<w->numpoints ; i++)
		glVertex3f (w->p[i][0],w->p[i][1],w->p[i][2] );
	glEnd ();

	glFlush ();
}