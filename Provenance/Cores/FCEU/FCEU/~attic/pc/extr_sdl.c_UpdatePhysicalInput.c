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
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  CloseGame () ; 
 scalar_t__ SDL_PollEvent (TYPE_1__*) ; 
#define  SDL_QUIT 128 
 int /*<<< orphan*/  puts (char*) ; 

void UpdatePhysicalInput(void)
{
 SDL_Event event;

 while(SDL_PollEvent(&event))
 {
  switch(event.type)
  {
   //case SDL_SYSWMEVENT: puts("Nifty keen");break;
   //case SDL_VIDEORESIZE: puts("Okie dokie");break;
   case SDL_QUIT: CloseGame();puts("Quit");break;
  }
  //printf("Event: %d\n",event.type);
  //fflush(stdout);
 }
 //SDL_PumpEvents();
}