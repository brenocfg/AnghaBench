#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ Uint32 ;
struct TYPE_6__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_5__ {int member_0; int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  TTF_Font ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  TYPE_1__ SDL_Rect ;
typedef  TYPE_2__ SDL_Color ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_FillRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_Flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockSurface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 scalar_t__ SDL_SRCALPHA ; 
 int /*<<< orphan*/  SDL_SetAlpha (int /*<<< orphan*/ *,scalar_t__,float) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int TTF_Init () ; 
 int /*<<< orphan*/ * TTF_OpenFont (char*,int) ; 
 int /*<<< orphan*/ * TTF_RenderText_Solid (int /*<<< orphan*/ *,char*,TYPE_2__) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  emscripten_get_canvas_element_size (char*,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char **argv) {
  Uint32 SRC_FLAG = SDL_SRCALPHA;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);

  if (argc > 1 && strcmp(argv[1], "-0") == 0) {
    SRC_FLAG = 0;
    SDL_FillRect(screen, 0, 0xFF00FF00);
  }

  printf("Init: %d\n", TTF_Init());

  TTF_Font *font = TTF_OpenFont("sans-serif", 40);
  printf("Font: %p\n", font);

  SDL_Color color = { 0xff, 0x99, 0x00, 0xff };
  SDL_Surface *text = TTF_RenderText_Solid(font, "hello orange world", color);

  // render
  for (int i = 0; i < 255; i++) {
    SDL_Rect dest = { i, i, 0, 0 };
    SDL_SetAlpha(text, SRC_FLAG, (((float)i)/255)*(((float)i)/255)*255);
    SDL_BlitSurface (text, NULL, screen, &dest);
  }

  SDL_Flip(screen); 

  SDL_LockSurface(screen);

  int width, height;
  emscripten_get_canvas_element_size("#canvas", &width, &height);

  if (width != 600 && height != 450)
  {
    printf("error: wrong width/height\n");
    abort();
  }

  SDL_Quit();

  printf("done.\n");

  return 0;
}