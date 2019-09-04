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
typedef  int /*<<< orphan*/  fbuf ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLubyte ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_GL_SwapBuffers () ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  glColor4f (double,double,double,int) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glTexCoordPointer (int,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexPointer (int,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  verify () ; 

int main(int argc, char *argv[])
{
    SDL_Surface *screen;
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    screen = SDL_SetVideoMode( 640, 480, 24, SDL_OPENGL );
    if ( !screen ) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    // Create a texture

    GLuint texture;
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    GLubyte textureData[]  = { 0x7f,    0,    0,
                                  0, 0xff,    0,
                               0x7f,    0,    0,
                                  0, 0xff,    0};
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0,
                  GL_RGB, GL_UNSIGNED_BYTE, textureData );


    // BEGIN

#if USE_GLEW
    glewInit();
#endif

    glClearColor( 0, 0, 0.5, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );

    glColor4f(0.8, 0.8, 0.8, 1);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    const int kRowSize = 20;
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    float fbuf[] = {0, 1, 0, 0, 1,
                    1, 1, 0, 1, 1,
                    1, 0, 0, 1, 0,
                    0, 1, 0, 0, 1,
                    1, 0, 0, 1, 0,
                    0, 0, 0, 0, 0};
    glBufferData(GL_ARRAY_BUFFER, sizeof(fbuf) * sizeof(float), fbuf, GL_STATIC_DRAW);

    glTexCoordPointer(2, GL_FLOAT, kRowSize, (GLvoid*)(3*4));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, kRowSize, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    // END

    SDL_GL_SwapBuffers();

    verify();

#ifndef __EMSCRIPTEN__
    SDL_Delay(1500);
#endif

    SDL_Quit();

    return 0;
}