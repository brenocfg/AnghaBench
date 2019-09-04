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
struct TYPE_3__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  int /*<<< orphan*/  TTF_Font ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  TYPE_1__ SDL_Color ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_FreeSurface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTF_Init () ; 
 int /*<<< orphan*/ * TTF_OpenFont (char*,int) ; 
 int /*<<< orphan*/ * TTF_RenderText_Solid (int /*<<< orphan*/ *,char*,TYPE_1__) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("myfont.ttf", 40);

    int i = 0;
    while (i < 200)
    {
        printf("%i\n", i);
        i++;

        SDL_Color color = { 0xff, 0x99, 0x00, 0xff };
        SDL_Surface *text = TTF_RenderText_Solid(font, "hello world", color);
        SDL_BlitSurface (text, NULL, screen, NULL);

        SDL_FreeSurface(text);
    }

#ifdef __EMSCRIPTEN__
    REPORT_RESULT(1);
#endif
}