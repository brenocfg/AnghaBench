#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sem_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroySemaphore (scalar_t__) ; 
 TYPE_1__ sdl_sync ; 

__attribute__((used)) static void sdl_sync_close()
{
  if(sdl_sync.sem_sync)
    SDL_DestroySemaphore(sdl_sync.sem_sync);
}