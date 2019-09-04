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
struct TYPE_5__ {int w; int h; int /*<<< orphan*/  pixels; } ;
typedef  TYPE_1__ SDL_Surface ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  double GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 TYPE_1__* IMG_Load (char*) ; 
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int /*<<< orphan*/  SDL_FreeSurface (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_GL_SwapBuffers () ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glLoadMatrixf (double*) ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexCoord2i (int,int) ; 
 int /*<<< orphan*/  glTexCoordPointer (int,int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertex2f (int,int) ; 
 int /*<<< orphan*/  glVertex2fv (float*) ; 
 int /*<<< orphan*/  glVertex3f (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertex3fv (float*) ; 
 int /*<<< orphan*/  glVertexPointer (int,int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[])
{
    SDL_Surface *screen;

    // Slightly different SDL initialization
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

    screen = SDL_SetVideoMode( 640, 480, 16, SDL_OPENGL ); // *changed*
    if ( !screen ) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    // Set the OpenGL state after creating the context with SDL_SetVideoMode

    glClearColor( 0, 0, 0, 0 );

    glEnable( GL_TEXTURE_2D ); // Needed when we're using the fixed-function pipeline.

    glViewport( 0, 0, 640, 480 );

    glMatrixMode( GL_PROJECTION );
    GLfloat matrixData[] = { 2.0/640,        0,  0,  0,
                                   0, -2.0/480,  0,  0,
                                   0,        0, -1,  0,
                                  -1,        1,  0,  1 };
    glLoadMatrixf(matrixData); // test loadmatrix

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Load the OpenGL texture

    GLuint texture; // Texture object handle
    SDL_Surface *surface; // Gives us the information to make the texture

    if ( (surface = IMG_Load("screenshot.png")) ) {

        // Check that the image's width is a power of 2
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("warning: image.bmp's width is not a power of 2\n");
        }

        // Also check if the height is a power of 2
        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("warning: image.bmp's height is not a power of 2\n");
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, &texture );

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, texture );

        // Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        //SDL_LockSurface(surface);

        // Add some greyness
        memset(surface->pixels, 0x66, surface->w*surface->h);

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );

        //SDL_UnlockSurface(surface);
    }
    else {
        printf("SDL could not load image.bmp: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }

    // Clear the screen before drawing
    glClear( GL_COLOR_BUFFER_BIT );

    // Bind the texture to which subsequent calls refer to
    glBindTexture( GL_TEXTURE_2D, texture );

    // Use clientside vertex pointers to render two items
    GLfloat vertexData[] = { 0, 0, 10, 10, // texture2, position2
                             1, 0, 300, 10,
                             1, 1, 300, 128,
                             0, 1, 10, 128,
                             0, 0.5, 410, 10,
                             1, 0.5, 600, 10,
                             1, 1, 630, 200,
                             0.5, 1, 310, 250 };

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 4*4, &vertexData[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 4*4, &vertexData[2]);

    glDrawArrays(GL_QUADS, 0, 8);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Render the last item using oldschool glBegin etc
    glBegin( GL_TRIANGLE_STRIP );
        glTexCoord2i( 0, 0 ); glVertex3f( 100, 300, 0 );
        glTexCoord2i( 1, 0 ); glVertex2f( 300, 300 );
        glTexCoord2i( 1, 1 ); { float vals[3] = { 300, 400, 0 }; glVertex3fv(vals); }
        glTexCoord2i( 0, 1 ); { float vals[2] = { 500, 410 }; glVertex2fv(vals); }
    glEnd();

    SDL_GL_SwapBuffers();

#ifndef __EMSCRIPTEN__
    // Wait for 3 seconds to give us a chance to see the image
    SDL_Delay(3000);
#endif

    // Now we can delete the OpenGL texture and close down SDL
    glDeleteTextures( 1, &texture );

    SDL_Quit();

    return 0;
}