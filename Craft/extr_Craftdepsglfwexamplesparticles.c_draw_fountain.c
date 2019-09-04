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
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int FOUNTAIN_SIDE_POINTS ; 
 int FOUNTAIN_SWEEP_STEPS ; 
 int /*<<< orphan*/  GL_COMPILE_AND_EXECUTE ; 
 int /*<<< orphan*/  GL_DIFFUSE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_SHININESS ; 
 int /*<<< orphan*/  GL_SPECULAR ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 double M_PI ; 
 scalar_t__ cos (double) ; 
 int /*<<< orphan*/  fountain_diffuse ; 
 float* fountain_normal ; 
 int /*<<< orphan*/  fountain_shininess ; 
 float* fountain_side ; 
 int /*<<< orphan*/  fountain_specular ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCallList (scalar_t__) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glEndList () ; 
 scalar_t__ glGenLists (int) ; 
 int /*<<< orphan*/  glMaterialf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glMaterialfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glNewList (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glNormal3f (float,float,float) ; 
 int /*<<< orphan*/  glVertex3f (float,float,float) ; 
 scalar_t__ sin (double) ; 

__attribute__((used)) static void draw_fountain(void)
{
    static GLuint fountain_list = 0;
    double angle;
    float  x, y;
    int m, n;

    // The first time, we build the fountain display list
    if (!fountain_list)
    {
        fountain_list = glGenLists(1);
        glNewList(fountain_list, GL_COMPILE_AND_EXECUTE);

        glMaterialfv(GL_FRONT, GL_DIFFUSE, fountain_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, fountain_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, fountain_shininess);

        // Build fountain using triangle strips
        for (n = 0;  n < FOUNTAIN_SIDE_POINTS - 1;  n++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for (m = 0;  m <= FOUNTAIN_SWEEP_STEPS;  m++)
            {
                angle = (double) m * (2.0 * M_PI / (double) FOUNTAIN_SWEEP_STEPS);
                x = (float) cos(angle);
                y = (float) sin(angle);

                // Draw triangle strip
                glNormal3f(x * fountain_normal[n * 2 + 2],
                           y * fountain_normal[n * 2 + 2],
                           fountain_normal[n * 2 + 3]);
                glVertex3f(x * fountain_side[n * 2 + 2],
                           y * fountain_side[n * 2 + 2],
                           fountain_side[n * 2 +3 ]);
                glNormal3f(x * fountain_normal[n * 2],
                           y * fountain_normal[n * 2],
                           fountain_normal[n * 2 + 1]);
                glVertex3f(x * fountain_side[n * 2],
                           y * fountain_side[n * 2],
                           fountain_side[n * 2 + 1]);
            }

            glEnd();
        }

        glEndList();
    }
    else
        glCallList(fountain_list);
}