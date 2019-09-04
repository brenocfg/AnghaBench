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
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  double GLdouble ;

/* Variables and functions */
 int /*<<< orphan*/  GL_AUTO_NORMAL ; 
 int GL_ENABLE_BIT ; 
 int GL_EVAL_BIT ; 
 int /*<<< orphan*/  GL_MAP2_TEXTURE_COORD_2 ; 
 int /*<<< orphan*/  GL_MAP2_VERTEX_3 ; 
 int /*<<< orphan*/  GL_NORMALIZE ; 
 double** cpdata ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEvalMesh2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glMap2d (int /*<<< orphan*/ ,double,double,int,int,double,double,int,int,double*) ; 
 int /*<<< orphan*/  glMapGrid2d (int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  glPopAttrib () ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushAttrib (int) ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glRotated (double,double,double,double) ; 
 int /*<<< orphan*/  glScaled (double,double,double) ; 
 int /*<<< orphan*/  glTranslated (double,double,double) ; 
 size_t** patchdata ; 
 double*** tex ; 

__attribute__((used)) static void fghTeapot( GLint grid, GLdouble scale, GLenum type )
{
#if defined(_WIN32_WCE)
		int i, numV=sizeof(strip_vertices)/4, numI=sizeof(strip_normals)/4;
#else
    double p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
    long i, j, k, l;
#endif

    glPushAttrib( GL_ENABLE_BIT | GL_EVAL_BIT );
    glEnable( GL_AUTO_NORMAL );
    glEnable( GL_NORMALIZE );
    glEnable( GL_MAP2_VERTEX_3 );
    glEnable( GL_MAP2_TEXTURE_COORD_2 );

    glPushMatrix();
    glRotated( 270.0, 1.0, 0.0, 0.0 );
    glScaled( 0.5 * scale, 0.5 * scale, 0.5 * scale );
    glTranslated( 0.0, 0.0, -1.5 );

#if defined(_WIN32_WCE)
    glRotated( 90.0, 1.0, 0.0, 0.0 );
    glBegin( GL_TRIANGLE_STRIP );

    for( i = 0; i < numV-1; i++ )
    {
        int vidx = strip_vertices[i],
            nidx = strip_normals[i];

        if( vidx != -1 )
        {
            glNormal3fv( normals[nidx]  );
            glVertex3fv( vertices[vidx] );
        }
        else
        {
            glEnd();
            glBegin( GL_TRIANGLE_STRIP );
        }
    }

    glEnd();
#else
    for (i = 0; i < 10; i++) {
      for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
          for (l = 0; l < 3; l++) {
            p[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
            q[j][k][l] = cpdata[patchdata[i][j * 4 + (3 - k)]][l];
            if (l == 1)
              q[j][k][l] *= -1.0;
            if (i < 6) {
              r[j][k][l] =
                cpdata[patchdata[i][j * 4 + (3 - k)]][l];
              if (l == 0)
                r[j][k][l] *= -1.0;
              s[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
              if (l == 0)
                s[j][k][l] *= -1.0;
              if (l == 1)
                s[j][k][l] *= -1.0;
            }
          }
        }
      }

      glMap2d(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
        &tex[0][0][0]);
      glMap2d(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4,
        &p[0][0][0]);
      glMapGrid2d(grid, 0.0, 1.0, grid, 0.0, 1.0);
      glEvalMesh2(type, 0, grid, 0, grid);
      glMap2d(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4,
        &q[0][0][0]);
      glEvalMesh2(type, 0, grid, 0, grid);
      if (i < 6) {
        glMap2d(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4,
          &r[0][0][0]);
        glEvalMesh2(type, 0, grid, 0, grid);
        glMap2d(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4,
          &s[0][0][0]);
        glEvalMesh2(type, 0, grid, 0, grid);
      }
    }
#endif  /* defined(_WIN32_WCE) */

    glPopMatrix();
    glPopAttrib();
}