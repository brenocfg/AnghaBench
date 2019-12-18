#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  DebugMessage (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M64MSG_ERROR ; 
 int /*<<< orphan*/  M64MSG_INFO ; 
 int SDL_INIT_AUDIO ; 
 int SDL_INIT_TIMER ; 
 scalar_t__ SDL_Init (int) ; 
 int critical_failure ; 

__attribute__((used)) static void InitializeSDL(void)
{
    DebugMessage(M64MSG_INFO, "Initializing SDL audio subsystem...");

    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        DebugMessage(M64MSG_ERROR, "Failed to initialize SDL audio subsystem; forcing exit.\n");
        critical_failure = 1;
        return;
    }
    critical_failure = 0;

}