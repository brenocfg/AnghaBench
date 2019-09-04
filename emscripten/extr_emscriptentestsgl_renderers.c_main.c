#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_7__ {double member_0; double member_1; } ;
struct TYPE_6__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_5__ {double member_0; double member_1; } ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  char GLbyte ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_COLOR_ARRAY ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DYNAMIC_DRAW ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int SDL_GL_GetSwapInterval () ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_GL_SetSwapInterval (int) ; 
 int /*<<< orphan*/  SDL_GL_SwapBuffers () ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColorPointer (int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  glDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexPointer (int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

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
    
#ifndef __EMSCRIPTEN__
    glEnable( GL_TEXTURE_2D ); // Need this to display a texture XXX unnecessary in OpenGL ES 2.0/WebGL
#endif

    glViewport( 0, 0, 640, 480 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    // Clear the screen before drawing
    glClear( GL_COLOR_BUFFER_BIT );
    
    typedef struct Vertex {
        GLfloat x;
        GLfloat y;
    } Vertex;
    
    typedef struct Color {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    } Color;
    
    typedef struct Type1 {
        Vertex location;
        Color  color;
    } Type1;
    
    typedef struct Type2 {
        GLuint unused1;
        Vertex location;
        GLfloat unused2;
        Color  color;
    } Type2;
    
    Type1 first[3] = {
        {{-1.0, 0.0}, {0xFF, 0x00, 0x00, 0xFF}},
        {{ 0.0, 1.0}, {0x00, 0xFF, 0x00, 0xFF}},
        {{ 1.0, 0.0}, {0x00, 0x00, 0xFF, 0xFF}}
    };
    
    Type2 second[3] = {
        {0.0, {-1.0,  0.0}, 0.0, {0xFF, 0x00, 0x00, 0xFF}},
        {0.0, { 1.0,  0.0}, 0.0, {0x00, 0x00, 0xFF, 0xFF}},
        {0.0, { 0.0, -1.0}, 0.0, {0x00, 0xFF, 0x00, 0xFF}}};
    
    // make two vbo objects
    GLuint vbo[2];
    glGenBuffers(2, &vbo[0]);
    
    // load the first into the context
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    
    // allocate enough space for 100 vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(Type1)*100, NULL, GL_DYNAMIC_DRAW);
    
    // load the second into the context
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    
    // allocate enough space for 100 vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(Type2)*100, NULL, GL_DYNAMIC_DRAW);
    
    // DRAW
    
    GLbyte * pointer;

    // Clear the screen before drawing
    glClear( GL_COLOR_BUFFER_BIT );
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    // FIRST
    // load the first into the context
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    
    // Load actual data in
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Type1)*3, &first[0]);
    
    // point to the buffer's location data
    glVertexPointer(2, GL_FLOAT, sizeof(Type1), NULL);
    
    pointer = (GLbyte*)(((GLbyte*)&first[0].color) - ((GLbyte*)&first[0].location));

    printf("location = %p\n", pointer);
    // point to the buffer's color data
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Type1), pointer);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    // SECOND
    
    // load the first into the context
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    
    // Load actual data in
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Type2)*3, &second[0]);
    
    pointer = (GLbyte*)((GLbyte*)&second[0].location - (GLbyte*)&second[0].unused1);
    
    // point to the buffer's location data
    printf("location = %p\n", pointer);
    glVertexPointer(2, GL_FLOAT, sizeof(Type2), pointer);
    
    pointer = (GLbyte*)((GLbyte*)&second[0].color - (GLbyte*)&second[0].unused1);
    
    // point to the buffer's location data
    printf("location = %p\n", pointer);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Type2), pointer);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    for(int i = 0; i <= 2; ++ i)
    {
        SDL_GL_SetSwapInterval(i);
        assert(SDL_GL_GetSwapInterval() == i);
    }

    SDL_GL_SwapBuffers();
    
#ifndef __EMSCRIPTEN__
    // Wait for 3 seconds to give us a chance to see the image
    SDL_Delay(3000);
#endif

    SDL_Quit();
    
    return 0;
}