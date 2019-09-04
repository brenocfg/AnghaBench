#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_15__ {int member_0; int member_1; int member_2; int member_3; int y; } ;
struct TYPE_14__ {int h; int w; scalar_t__ pixels; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  TTF_Font ;
typedef  TYPE_1__ SDL_Surface ;
typedef  TYPE_2__ SDL_Rect ;
typedef  TYPE_3__ SDL_Color ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_FillRect (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Flip (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockSurface (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_MapRGBA (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int TTF_Init () ; 
 int /*<<< orphan*/ * TTF_OpenFont (char*,int) ; 
 TYPE_1__* TTF_RenderText_Solid (int /*<<< orphan*/ *,char*,TYPE_3__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char **argv) {
#ifdef __EMSCRIPTEN__
  // include GL stuff, to check that we can compile hybrid 2d/GL apps
  extern void glBegin(int mode);
  extern void glBindBuffer(int target, int buffer);
  if (argc == 9876) {
    glBegin(0);
    glBindBuffer(0, 0);
  }
#endif

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);

  printf("Init: %d\n", TTF_Init());

  TTF_Font *font = TTF_OpenFont("sans-serif", 40);
  printf("Font: %p\n", font);

  SDL_Color color = { 0xff, 0x99, 0x00, 0xff };

  SDL_Surface *text = TTF_RenderText_Solid(font, "hello orange world", color);

  SDL_Color color2 = { 0xbb, 0, 0xff, 0xff };
  SDL_Surface *text2 = TTF_RenderText_Solid(font, "a second line, purple", color2);

  // render
  SDL_Rect dest = { 0, 50, 0, 0 };
  SDL_BlitSurface (text, NULL, screen, NULL);
  dest.y = 100;
  SDL_BlitSurface (text2, NULL, screen, &dest);

  // fill stuff
  SDL_Rect rect = { 200, 200, 175, 125 };
  SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, 0x22, 0x22, 0xff, 0xff));

  SDL_Flip(screen); 

  SDL_LockSurface(screen);

  int sum = 0;
  for (int i = 0; i < screen->h; i++) {
    sum += *((char*)screen->pixels + i*screen->w*4 + i*4 + 0);
  }
  printf("Sum: %d\n", sum);

  printf("you should see two lines of text in different colors and a blue rectangle\n");

  SDL_Quit();

  printf("done.\n");

  return 0;
}