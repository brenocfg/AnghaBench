#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int member_0; int member_1; int member_2; int member_3; int x; int y; int w; int h; } ;
struct TYPE_16__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ SDL_Surface ;
typedef  TYPE_2__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (TYPE_1__*,TYPE_2__*,TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* SDL_CreateRGBSurface (int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SDL_FillRect (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GetClipRect (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_MapRGB (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SDL_MapRGBA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  SDL_SetClipRect (TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UpdateRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int height ; 
 int /*<<< orphan*/  printf (char*) ; 
 int width ; 

int main() {
  SDL_Rect rect = {0, 0, width, height};
  SDL_Rect firstRect = {10, 10, 50, 100};
  SDL_Rect secondRect = {30, 50, 100, 100};

  SDL_Rect firstRectForFill = {240 + 10, 10, 50, 100};
  SDL_Rect secondRectForFill = {240 + 30, 50, 100, 100};

  SDL_Rect rectForTest = {0, 0, 0, 0};
  SDL_Rect lastRect = { 100, 150, 120, 40};

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *dst = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
  SDL_Surface *src = SDL_CreateRGBSurface(0, width, height, 32, 
    0x000000ff, 
    0x0000ff00, 
    0x00ff0000, 
    0xff000000);

  /* Fill dst with yellow color */
  SDL_FillRect(src, &rect, SDL_MapRGB(src->format, 255, 255, 0));
  SDL_FillRect(dst, &rect, SDL_MapRGB(dst->format, 0, 0, 0));
  SDL_SetClipRect(dst, NULL);
  SDL_BlitSurface(src, &rect, dst, &rect);

  /* Draw red on dst */
  SDL_FillRect(src, &rect, SDL_MapRGB(src->format, 255, 0, 0));
  SDL_SetClipRect(dst, &firstRect);
  SDL_BlitSurface(src, &rect, dst, &rect);

  assert(rect.x = firstRect.x);
  assert(rect.y = firstRect.y);
  assert(rect.w = firstRect.w);
  assert(rect.h = firstRect.h);

  /* Draw green rect on red rect */
  SDL_FillRect(src, &rect, SDL_MapRGB(src->format, 0, 255, 0));
  SDL_SetClipRect(dst, &secondRect);
  SDL_BlitSurface(src, &rect, dst, &rect);

  assert(rect.x = secondRect.x);
  assert(rect.y = secondRect.y);
  assert(rect.w = firstRect.x + firstRect.w);
  assert(rect.h = firstRect.h + firstRect.h);

  /* Same with fill rect */
  rect.x = 0; rect.y = 0;
  rect.w = width; rect.h = height;

  SDL_SetClipRect(dst, &firstRectForFill);
  SDL_FillRect(dst, &rect, SDL_MapRGB(dst->format, 0, 0, 255));

  assert(rect.x = firstRectForFill.x);
  assert(rect.y = firstRectForFill.y);
  assert(rect.w = firstRectForFill.w);
  assert(rect.h = firstRectForFill.h);

  SDL_SetClipRect(dst, &secondRectForFill);
  SDL_FillRect(dst, &rect, SDL_MapRGBA(dst->format, 255, 0, 255, 255));

  assert(rect.x = secondRectForFill.x);
  assert(rect.y = secondRectForFill.y);
  assert(rect.w = firstRectForFill.x + firstRectForFill.w);
  assert(rect.h = firstRectForFill.h + firstRectForFill.h);

  SDL_GetClipRect(dst, &rectForTest);
  assert(rectForTest.x == 270);
  assert(rectForTest.y == 50);
  assert(rectForTest.w == 50);
  assert(rectForTest.h == 100);

  SDL_SetClipRect(dst, 0);
  SDL_FillRect(dst, &lastRect, SDL_MapRGBA(dst->format, 255, 0, 0, 255));
  SDL_UpdateRect(dst, 0, 0, width, height);

  printf("There should be yellow background\n");
  printf("One the left side there should be red rect with green rect inside\n");
  printf("One the right side there should be blue rect with pink rect inside\n");

  SDL_Quit();

  return 0;
}