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
struct TYPE_3__ {int x; int y; int w; int h; } ;
typedef  TYPE_1__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_RenderClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderFillRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_RenderPresent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetRenderDrawColor (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  renderer ; 

void frame()
{
    static int x = 0;
    static int y = 0;
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 100;
    rect.h = 100;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}