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
typedef  void* vec_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_FILL ; 
 int /*<<< orphan*/  GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_POLYGON ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  InitWindow () ; 
 void** draw_maxs ; 
 void** draw_mins ; 
 int /*<<< orphan*/  drawflag ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor3f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor4f (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glFlush () ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertex3f (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gluLookAt (void*,void*,void*,void*,void*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gluPerspective (int,int,int,int) ; 
 int qtrue ; 

void Draw_ClearWindow (void)
{
	static int	init;
	int		w, h, g;
	vec_t	mx, my;

	if (!drawflag)
		return;

	if (!init)
	{
		init = qtrue;
		InitWindow ();
	}

	glClearColor (1,0.8,0.8,0);
	glClear (GL_COLOR_BUFFER_BIT);

	w = (draw_maxs[0] - draw_mins[0]);
	h = (draw_maxs[1] - draw_mins[1]);

	mx = draw_mins[0] + w/2;
	my = draw_mins[1] + h/2;

	g = w > h ? w : h;

	glLoadIdentity ();
    gluPerspective (90,  1,  2,  16384);
	gluLookAt (mx, my, draw_maxs[2] + g/2, mx , my, draw_maxs[2], 0, 1, 0);

	glColor3f (0,0,0);
//	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glDisable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if 0
	glColor4f (1,0,0,0.5);
	glBegin (GL_POLYGON);

	glVertex3f (0, 500, 0);
	glVertex3f (0, 900, 0);
	glVertex3f (0, 900, 100);
	glVertex3f (0, 500, 100);

	glEnd ();
#endif

	glFlush ();

}