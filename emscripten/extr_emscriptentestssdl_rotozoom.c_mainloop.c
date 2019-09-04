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
struct TYPE_3__ {int member_2; int member_3; int x; int y; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_UpdateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int numSprites ; 
 int /*<<< orphan*/  screen ; 
 int /*<<< orphan*/ * sprite ; 

void mainloop() {
    int i;
    int row = 0;
    SDL_Rect rect = { 0, 0, 100, 100 };
    for (i = 0; i < numSprites; i++) {
        rect.x = i & 1 ? 200 : 0;
        rect.y = row * 200;
        row += i & 1;
        SDL_BlitSurface(sprite[i], 0, screen, &rect);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
}