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
struct SDL_version {int /*<<< orphan*/  patch; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_TIMER ; 
 int SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_VERSION (struct SDL_version*) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int usb_init () ; 

__attribute__((used)) static int carlu_init()
{
	struct SDL_version compiled;
	int ret;

	SDL_VERSION(&compiled);
	dbg("=== SDL %d.%d.%d ===\n", compiled.major, compiled.minor, compiled.patch);

	ret = SDL_Init(SDL_INIT_TIMER);
	if (ret != 0) {
		err("Unable to initialize SDL: (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	return usb_init();
}