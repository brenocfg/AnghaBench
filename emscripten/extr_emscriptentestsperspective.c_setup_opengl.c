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
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_CCW ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_SMOOTH ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFrontFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShadeModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gluPerspective (double,float,double,double) ; 

__attribute__((used)) static void setup_opengl( int width, int height )
{
    float ratio = (float) width / (float) height;
    
    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );
    
    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
    
    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );
    
    /* Setup our viewport. */
    glViewport( 0, 0, width, height );
    
    /*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    /*
     * EXERCISE:
     * Replace this with a call to glFrustum.
     */
    gluPerspective( 60.0, ratio, 1.0, 1024.0 );
}