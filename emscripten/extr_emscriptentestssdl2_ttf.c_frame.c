#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_6__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SDL_Texture ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  TYPE_1__ SDL_Rect ;
typedef  TYPE_2__ SDL_Color ;

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateTextureFromSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_DestroyTexture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_FreeSurface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_RenderClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_RenderPresent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetRenderDrawColor (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/ * TTF_RenderText_Shaded (int /*<<< orphan*/ ,char*,TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  font ; 
 int /*<<< orphan*/  renderer ; 

void frame()
{
    static SDL_Color colorA = { 0xff, 0x99, 0x00, 0xff };
    static SDL_Color colorB = { 0x11, 0xff, 0xff, 0xff };
    static SDL_Rect upperRect = {0, 0, 640, 240};
    static SDL_Rect lowerRect = {0, 240, 640, 240};

    SDL_Surface *helloSurface = TTF_RenderText_Shaded(font, "hello", colorA, colorB);
    SDL_Surface *worldSurface = TTF_RenderText_Shaded(font, "world", colorB, colorA);
    SDL_Texture *helloTexture = SDL_CreateTextureFromSurface(renderer, helloSurface);
    SDL_Texture *worldTexture = SDL_CreateTextureFromSurface(renderer, worldSurface);

    SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, helloTexture, NULL, &upperRect);
    SDL_RenderCopy(renderer, worldTexture, NULL, &lowerRect);
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(helloSurface);
    SDL_FreeSurface(worldSurface);
    SDL_DestroyTexture(helloTexture);
    SDL_DestroyTexture(worldTexture);
}