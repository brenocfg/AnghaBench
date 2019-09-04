#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; } ;
typedef  TYPE_1__ VideoState ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_SetWindowFullscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetWindowPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetWindowSize (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SDL_SetWindowTitle (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SDL_ShowWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WINDOW_FULLSCREEN_DESKTOP ; 
 int default_height ; 
 int default_width ; 
 scalar_t__ input_filename ; 
 scalar_t__ is_full_screen ; 
 int screen_height ; 
 int /*<<< orphan*/  screen_left ; 
 int /*<<< orphan*/  screen_top ; 
 int screen_width ; 
 int /*<<< orphan*/  window ; 
 scalar_t__ window_title ; 

__attribute__((used)) static int video_open(VideoState *is)
{
    int w,h;

    w = screen_width ? screen_width : default_width;
    h = screen_height ? screen_height : default_height;

    if (!window_title)
        window_title = input_filename;
    SDL_SetWindowTitle(window, window_title);

    SDL_SetWindowSize(window, w, h);
    SDL_SetWindowPosition(window, screen_left, screen_top);
    if (is_full_screen)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_ShowWindow(window);

    is->width  = w;
    is->height = h;

    return 0;
}