#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* vfmt; } ;
struct TYPE_4__ {int BitsPerPixel; } ;
typedef  TYPE_2__ SDL_VideoInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_Delay (int) ; 
 char* SDL_GetError () ; 
 TYPE_2__* SDL_GetVideoInfo () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int SDL_OPENGL ; 
 scalar_t__ SDL_SetVideoMode (int,int,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  one_iter () ; 
 int /*<<< orphan*/  quit_tutorial (int) ; 
 int /*<<< orphan*/  setup_opengl (int,int) ; 
 int /*<<< orphan*/  stderr ; 

int main( int argc, char* argv[] )
{
    /* Information about the current video settings. */
    const SDL_VideoInfo* info = NULL;
    /* Dimensions of our window. */
    int width = 0;
    int height = 0;
    /* Color depth in bits of our window. */
    int bpp = 0;
    /* Flags we will pass into SDL_SetVideoMode. */
    int flags = 0;
    
    /* First, initialize SDL's video subsystem. */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n",
                SDL_GetError( ) );
        quit_tutorial( 1 );
    }
    
    /* Let's get some video information. */
    info = SDL_GetVideoInfo( );
    
    if( !info ) {
        /* This should probably never happen. */
        fprintf( stderr, "Video query failed: %s\n",
                SDL_GetError( ) );
        quit_tutorial( 1 );
    }
    
    /*
     * Set our width/height to 640/480 (you would
     * of course let the user decide this in a normal
     * app). We get the bpp we will request from
     * the display. On X11, VidMode can't change
     * resolution, so this is probably being overly
     * safe. Under Win32, ChangeDisplaySettings
     * can change the bpp.
     */
    width = 640;
    height = 480;
    bpp = info->vfmt->BitsPerPixel;
    
    /*
     * Now, we want to setup our requested
     * window attributes for our OpenGL window.
     * We want *at least* 5 bits of red, green
     * and blue. We also want at least a 16-bit
     * depth buffer.
     *
     * The last thing we do is request a double
     * buffered window. '1' turns on double
     * buffering, '0' turns it off.
     *
     * Note that we do not use SDL_DOUBLEBUF in
     * the flags to SDL_SetVideoMode. That does
     * not affect the GL attribute state, only
     * the standard 2D blitting setup.
     */
//    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
//    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
//    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
//    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
//    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    /*
     * We want to request that SDL provide us
     * with an OpenGL window, in a fullscreen
     * video mode.
     *
     * EXERCISE:
     * Make starting windowed an option, and
     * handle the resize events properly with
     * glViewport.
     */
    flags = SDL_OPENGL;// | SDL_FULLSCREEN;
    
    /*
     * Set the video mode
     */
    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
        /*
         * This could happen for a variety of reasons,
         * including DISPLAY not being set, the specified
         * resolution not being available, etc.
         */
        fprintf( stderr, "Video mode set failed: %s\n",
                SDL_GetError( ) );
        quit_tutorial( 1 );
    }
    
    /*
     * At this point, we should have a properly setup
     * double-buffered window for use with OpenGL.
     */
    setup_opengl( width, height );
    
    /*
     * Now we want to begin our normal app process--
     * an event loop with a lot of redrawing.
     */
    one_iter(); // just one for testing purposes

#ifndef __EMSCRIPTEN__
    SDL_Delay(2000);
#endif    
    
    /*
     * EXERCISE:
     * Record timings using SDL_GetTicks() and
     * and print out frames per second at program
     * end.
     */
    
    /* Never reached. */
    return 0;
}