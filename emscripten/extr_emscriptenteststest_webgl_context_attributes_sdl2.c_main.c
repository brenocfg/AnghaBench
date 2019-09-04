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
typedef  int /*<<< orphan*/  SDL_Window ;
typedef  int /*<<< orphan*/  SDL_Renderer ;
typedef  int /*<<< orphan*/  SDL_GLContext ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_CreateRenderer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_CreateWindow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GL_ALPHA_SIZE ; 
 int /*<<< orphan*/  SDL_GL_CreateContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_GL_DEPTH_SIZE ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int /*<<< orphan*/  SDL_GL_MULTISAMPLEBUFFERS ; 
 int /*<<< orphan*/  SDL_GL_MULTISAMPLESAMPLES ; 
 int /*<<< orphan*/  SDL_GL_STENCIL_SIZE ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WINDOWPOS_UNDEFINED ; 
 int /*<<< orphan*/  SDL_WINDOW_OPENGL ; 
 int /*<<< orphan*/  WINDOWS_SIZE ; 
 int /*<<< orphan*/  checkContextAttributesSupport () ; 
 int /*<<< orphan*/  draw () ; 
 int /*<<< orphan*/  glewInit () ; 
 int /*<<< orphan*/  initGlObjects () ; 
 int /*<<< orphan*/  result ; 

int main(int argc, char *argv[]) {
    
    checkContextAttributesSupport(); 
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifdef AA_ACTIVATED
    antiAliasingActivated = true;
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
#else
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
#endif
    
#ifdef DEPTH_ACTIVATED
    depthActivated = true;
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
#else
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
#endif
    
#ifdef STENCIL_ACTIVATED
    stencilActivated = true;
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#else
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
#endif

#ifdef ALPHA_ACTIVATED
    alphaActivated = true;
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
#else
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
#endif
    
    SDL_Window *sdlWindow = SDL_CreateWindow("test",
					   SDL_WINDOWPOS_UNDEFINED,
					   SDL_WINDOWPOS_UNDEFINED,
					   WINDOWS_SIZE, WINDOWS_SIZE,
					   SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
    SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);

    glewInit();
    initGlObjects();
    
    draw();
        
    REPORT_RESULT(result);
    
    return 0;
}