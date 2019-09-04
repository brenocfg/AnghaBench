#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ show_mode; scalar_t__ video_st; scalar_t__ audio_st; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ VideoState ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_RenderClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderPresent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetRenderDrawColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SHOW_MODE_VIDEO ; 
 int /*<<< orphan*/  renderer ; 
 int /*<<< orphan*/  video_audio_display (TYPE_1__*) ; 
 int /*<<< orphan*/  video_image_display (TYPE_1__*) ; 
 int /*<<< orphan*/  video_open (TYPE_1__*) ; 

__attribute__((used)) static void video_display(VideoState *is)
{
    if (!is->width)
        video_open(is);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (is->audio_st && is->show_mode != SHOW_MODE_VIDEO)
        video_audio_display(is);
    else if (is->video_st)
        video_image_display(is);
    SDL_RenderPresent(renderer);
}