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
typedef  int /*<<< orphan*/  SDL_Surface ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FillRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instruction () ; 
 int /*<<< orphan*/  main_tick ; 

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);
  SDL_FillRect(screen, NULL, 0xFF000000);
  instruction();
  emscripten_set_main_loop(main_tick, 0, 0);

#ifdef AUTOMATE_SUCCESS
  EM_ASM(
    function sendEvent(type, data) {
      var event = document.createEvent('Event');
      event.initEvent(type, true, true);
      for(var d in data) event[d] = data[d];
      Module['canvas'].dispatchEvent(event);
    }
    // Scroll up by a tiny amount.
    sendEvent('wheel', { screenX: 1, screenY: 1, clientX: 1, clientY: 1, button: 0, buttons: 0, 'deltaX': 0, 'deltaY': -0.1, 'deltaZ': 0, 'deltaMode': 1 });
    // Scroll down by a tiny amount.
    sendEvent('wheel', { screenX: 1, screenY: 1, clientX: 1, clientY: 1, button: 0, buttons: 0, 'deltaX': 0, 'deltaY': 0.1, 'deltaZ': 0, 'deltaMode': 1 });
    // Press mouse middle button.
    sendEvent('mousedown', { screenX: 1, screenY: 1, clientX: 1, clientY: 1, button: 1, buttons: 2 });
  );
#endif
}