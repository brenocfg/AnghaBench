#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float r; float g; float b; int a; } ;
struct TYPE_6__ {TYPE_1__* format; } ;
struct TYPE_5__ {int /*<<< orphan*/  palette; } ;

/* Variables and functions */
 int COLOR_COUNT ; 
 int /*<<< orphan*/  SDL_SetPaletteColors (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* pal ; 
 TYPE_2__* screen ; 

void pallete(int red, int green, int blue) {
  //initialize sdl palette
  //with gradient colors
  pal[0].r = 0;
  pal[0].g = 0;
  pal[0].b = 0;
  pal[0].a = 255;

  for (int i=1; i< 1 + COLOR_COUNT; i++) {
    pal[i].r = (float) red    / COLOR_COUNT * i;
    pal[i].g = (float) green  / COLOR_COUNT * i;
    pal[i].b = (float) blue   / COLOR_COUNT * i;
    pal[i].a = 255;
  }

  SDL_SetPaletteColors(screen->format->palette, pal, 0, 1 + COLOR_COUNT);
}