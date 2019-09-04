#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int Uint8 ;
typedef  int /*<<< orphan*/  Uint32 ;
struct TYPE_8__ {int member_2; int member_3; int x; int y; int w; int h; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ SDL_Surface ;
typedef  TYPE_2__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FillRect (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GetRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  SDL_GetRGBA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_MapRGB (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SDL_MapRGBA (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UpdateRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main() {
  Uint32 c;
  Uint8 r, g, b, a;
  SDL_Rect rect = {0,0,300,450};

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);

  c = SDL_MapRGB(screen->format, 0xff, 0x00, 0x00); // OPAQUE RED
  SDL_GetRGB(c, screen->format, &r, &g, &b);
  assert(r == 0xff);
  assert(g == 0x00);
  assert(b == 0x00);
  SDL_FillRect(screen, &rect, c);
  rect.x = 300;
  c = SDL_MapRGB(screen->format, 0x7f, 0x7f, 0x00); // OPAQUE MUSTARD
  SDL_GetRGB(c, screen->format, &r, &g, &b);
  assert(r == 0x7f);
  assert(g == 0x7f);
  assert(b == 0x00);
  SDL_FillRect(screen, &rect, c);
  rect.x = 150;
  rect.y = 112;
  rect.w = 300;
  rect.h = 225;
  c = SDL_MapRGBA(screen->format, 0xff, 0xff, 0xff, 0xff); // OPAQUE WHITE
  SDL_GetRGBA(c, screen->format, &r, &g, &b, &a);
  assert(r == 0xff);
  assert(g == 0xff);
  assert(b == 0xff);
  assert(a == 0xff);
  SDL_FillRect(screen, &rect, c);
  c = SDL_MapRGBA(screen->format, 0x00, 0x00, 0x00, 0x00); // TRANSPARENT BLACK
  SDL_GetRGBA(c, screen->format, &r, &g, &b, &a);
  assert(r == 0x00);
  assert(g == 0x00);
  assert(b == 0x00);
  assert(a == 0x00);
  SDL_FillRect(screen, &rect, c);
  SDL_UpdateRect(screen, 0, 0, 600, 450);

  printf("The left half should be red and the right half mustard.\n");
  printf("There should be a white rectangle in the center.\n");

  SDL_Quit();

  return 0;
}