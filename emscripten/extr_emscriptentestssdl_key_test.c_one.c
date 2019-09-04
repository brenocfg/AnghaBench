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
struct TYPE_5__ {size_t sym; int scancode; } ;
struct TYPE_6__ {TYPE_1__ keysym; } ;
struct TYPE_7__ {int type; TYPE_2__ key; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
#define  SDL_KEYDOWN 129 
#define  SDL_KEYUP 128 
 scalar_t__ SDL_PollEvent (TYPE_3__*) ; 
 int* keys ; 
 int /*<<< orphan*/  printf (char*,size_t,int) ; 

void one() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_KEYDOWN:
        if (!keys[event.key.keysym.sym]) {
          keys[event.key.keysym.sym] = 1;
          printf("key down: sym %d scancode %d\n", event.key.keysym.sym, event.key.keysym.scancode);
        }
        break;
      case SDL_KEYUP:
        if (keys[event.key.keysym.sym]) {
          keys[event.key.keysym.sym] = 0;
          printf("key up: sym %d scancode %d\n", event.key.keysym.sym, event.key.keysym.scancode);
        }
        break;
    }
  }
}