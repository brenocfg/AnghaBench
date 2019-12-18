#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float member_0; float member_1; float member_2; } ;
typedef  TYPE_1__ vec3 ;
typedef  scalar_t__ mat4x4 ;
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_LINES ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glColor3f (float,float,float) ; 
 int /*<<< orphan*/  glDepthMask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glLoadMatrixf (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glVertex3f (float,float,float) ; 
 int /*<<< orphan*/  mat4x4_look_at (scalar_t__,TYPE_1__,TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void drawGrid(float scale, int steps)
{
    int i;
    float x, y;
    mat4x4 view;

    glPushMatrix();

    // Set background to some dark bluish grey
    glClearColor(0.05f, 0.05f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Setup modelview matrix (flat XY view)
    {
        vec3 eye = { 0.f, 0.f, 1.f };
        vec3 center = { 0.f, 0.f, 0.f };
        vec3 up = { 0.f, 1.f, 0.f };
        mat4x4_look_at(view, eye, center, up);
    }
    glLoadMatrixf((const GLfloat*) view);

    // We don't want to update the Z-buffer
    glDepthMask(GL_FALSE);

    // Set grid color
    glColor3f(0.0f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    // Horizontal lines
    x = scale * 0.5f * (float) (steps - 1);
    y = -scale * 0.5f * (float) (steps - 1);
    for (i = 0;  i < steps;  i++)
    {
        glVertex3f(-x, y, 0.0f);
        glVertex3f(x, y, 0.0f);
        y += scale;
    }

    // Vertical lines
    x = -scale * 0.5f * (float) (steps - 1);
    y = scale * 0.5f * (float) (steps - 1);
    for (i = 0;  i < steps;  i++)
    {
        glVertex3f(x, -y, 0.0f);
        glVertex3f(x, y, 0.0f);
        x += scale;
    }

    glEnd();

    // Enable Z-buffer writing again
    glDepthMask(GL_TRUE);

    glPopMatrix();
}