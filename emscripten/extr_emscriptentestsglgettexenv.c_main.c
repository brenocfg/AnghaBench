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
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  scalar_t__ GLint ;
typedef  float GLfloat ;

/* Variables and functions */
 scalar_t__ GL_BLEND ; 
 scalar_t__ GL_MODULATE ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_COLOR ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_MODE ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  glGetTexEnvfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glGetTexEnviv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  glTexEnvfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glTexEnvi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

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

    GLint value = 0;
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &value);
    assert(value == GL_BLEND);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &value);
    assert(value == GL_MODULATE);

    GLfloat colora[4] = { 0.2f, 0.3f, 0.4f, 0.5f };
    GLfloat colorb[4] = {};
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, colora);
    glGetTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, colorb);
    printf("%f %f %f %f\n", colorb[0], colorb[1], colorb[2], colorb[3]);
    assert(colora[0] == colorb[0]);
    assert(colora[1] == colorb[1]);
    assert(colora[2] == colorb[2]);
    assert(colora[3] == colorb[3]);
    SDL_Quit();
    
#ifdef REPORT_RESULT
    REPORT_RESULT(1);
#endif
    return 0;
}