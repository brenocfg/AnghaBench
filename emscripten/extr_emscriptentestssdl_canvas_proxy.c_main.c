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
struct TYPE_7__ {int /*<<< orphan*/  (* close ) () ;} ;
struct TYPE_6__ {int w; int h; scalar_t__ pixels; } ;
typedef  TYPE_1__ SDL_Surface ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EM_ASM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockSurface (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockSurface (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_2__ window ; 

int main(int argc, char **argv) {
  FILE *f = fopen("data.txt", "rb");
  assert(f);
  assert(fgetc(f) == 'd');
  assert(fgetc(f) == 'a');
  assert(fgetc(f) == 't');
  assert(fgetc(f) == 'u');
  assert(fgetc(f) == 'm');
  fclose(f);

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);

  SDL_LockSurface(screen);
  unsigned int *pixels = (unsigned int *)screen->pixels;
  for (int x = 0; x < screen->w; x++) {
    for (int y = 0; y < screen->h; y++) {
      pixels[x + y*screen->h] = x < 300 ? (y < 200 ? 0x3377AA88 : 0xAA3377CC) : (y < 200 ? 0x0066AA77 : 0xAA006699);
    }
  }
  SDL_UnlockSurface(screen);

  SDL_Quit();

  EM_ASM(window.close());
  return 0;
}