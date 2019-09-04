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
typedef  int GLubyte ;
typedef  float GLfloat ;

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  SDL_GL_SwapBuffers () ; 
 int /*<<< orphan*/  emColor4ubv (int*) ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glRotatef (float,double,double,double) ; 
 int /*<<< orphan*/  glTranslatef (double,double,double) ; 
 int /*<<< orphan*/  glVertex3fv (float*) ; 
 scalar_t__ should_rotate ; 

__attribute__((used)) static void draw_screen( void )
{
    /* Our angle of rotation. */
    static float angle = 0.0f;
    
    /*
     * EXERCISE:
     * Replace this awful mess with vertex
     * arrays and a call to glDrawElements.
     *
     * EXERCISE:
     * After completing the above, change
     * it to use compiled vertex arrays.
     *
     * EXERCISE:
     * Verify my windings are correct here ;).
     */
    static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
    static GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
    static GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
    static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
    static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
    static GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
    static GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
    static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
    static GLubyte red[]    = { 255,   0,   0, 255 };
    static GLubyte green[]  = {   0, 255,   0, 255 };
    static GLubyte blue[]   = {   0,   0, 255, 255 };
    static GLubyte white[]  = { 255, 255, 255, 255 };
    static GLubyte yellow[] = {   0, 255, 255, 255 };
    static GLubyte black[]  = {   0,   0,   0, 255 };
    static GLubyte orange[] = { 255, 255,   0, 255 };
    static GLubyte purple[] = { 255,   0, 255,   0 };
    
    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    
    /* Move down the z-axis. */
    glTranslatef( 0.0, 0.0, -5.0 );
    
    /* Rotate. */
    glRotatef( angle, 0.0, 1.0, 0.0 );
    
    if( should_rotate ) {
        
        if( ++angle > 360.0f ) {
            angle = 0.0f;
        }
        
    }
    
    /* Send our triangle data to the pipeline. */
    glBegin( GL_TRIANGLES );
    
    emColor4ubv( red );
    glVertex3fv( v0 );
    emColor4ubv( green );
    glVertex3fv( v1 );
    emColor4ubv( blue );
    glVertex3fv( v2 );
    
    emColor4ubv( red );
    glVertex3fv( v0 );
    emColor4ubv( blue );
    glVertex3fv( v2 );
    emColor4ubv( white );
    glVertex3fv( v3 );
    
    emColor4ubv( green );
    glVertex3fv( v1 );
    emColor4ubv( black );
    glVertex3fv( v5 );
    emColor4ubv( orange );
    glVertex3fv( v6 );
    
    emColor4ubv( green );
    glVertex3fv( v1 );
    emColor4ubv( orange );
    glVertex3fv( v6 );
    emColor4ubv( blue );
    glVertex3fv( v2 );
    
    emColor4ubv( black );
    glVertex3fv( v5 );
    emColor4ubv( yellow );
    glVertex3fv( v4 );
    emColor4ubv( purple );
    glVertex3fv( v7 );
    
    emColor4ubv( black );
    glVertex3fv( v5 );
    emColor4ubv( purple );
    glVertex3fv( v7 );
    emColor4ubv( orange );
    glVertex3fv( v6 );
    
    emColor4ubv( yellow );
    glVertex3fv( v4 );
    emColor4ubv( red );
    glVertex3fv( v0 );
    emColor4ubv( white );
    glVertex3fv( v3 );
    
    emColor4ubv( yellow );
    glVertex3fv( v4 );
    emColor4ubv( white );
    glVertex3fv( v3 );
    emColor4ubv( purple );
    glVertex3fv( v7 );
    
    emColor4ubv( white );
    glVertex3fv( v3 );
    emColor4ubv( blue );
    glVertex3fv( v2 );
    emColor4ubv( orange );
    glVertex3fv( v6 );
    
    emColor4ubv( white );
    glVertex3fv( v3 );
    emColor4ubv( orange );
    glVertex3fv( v6 );
    emColor4ubv( purple );
    glVertex3fv( v7 );
    
    emColor4ubv( green );
    glVertex3fv( v1 );
    emColor4ubv( red );
    glVertex3fv( v0 );
    emColor4ubv( yellow );
    glVertex3fv( v4 );
    
    emColor4ubv( green );
    glVertex3fv( v1 );
    emColor4ubv( yellow );
    glVertex3fv( v4 );
    emColor4ubv( black );
    glVertex3fv( v5 );
    
    glEnd( );
    
    /*
     * EXERCISE:
     * Draw text telling the user that 'Spc'
     * pauses the rotation and 'Esc' quits.
     * Do it using vetors and textured quads.
     */
    
    /*
     * Swap the buffers. This this tells the driver to
     * render the next frame from the contents of the
     * back-buffer, and to set all rendering operations
     * to occur on what was the front-buffer.
     *
     * Double buffering prevents nasty visual tearing
     * from the application drawing on areas of the
     * screen that are being updated at the same time.
     */
    SDL_GL_SwapBuffers( );
}