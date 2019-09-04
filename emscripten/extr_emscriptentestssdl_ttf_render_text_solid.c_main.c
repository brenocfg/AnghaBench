#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_9__ {int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  TTF_Font ;
typedef  TYPE_1__ SDL_Surface ;
typedef  TYPE_2__ SDL_Color ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_FillRect (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_MapRGB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTF_Init () ; 
 int /*<<< orphan*/ * TTF_OpenFont (char*,int) ; 
 TYPE_1__* TTF_RenderText_Solid (int /*<<< orphan*/ *,char*,TYPE_2__) ; 

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(320, 32, 32, SDL_HWSURFACE);

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Arial", 32);

    SDL_Color color = { 0xff, 0x99, 0x00, 0xff };
    SDL_Surface *text = TTF_RenderText_Solid(font, "Play", color);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
    SDL_BlitSurface(text, NULL, screen, NULL);
    return 0;
}