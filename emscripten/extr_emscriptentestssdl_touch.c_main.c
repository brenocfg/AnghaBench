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
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  progress () ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);

  progress();

#ifdef AUTOMATE_SUCCESS
  EM_ASM(
    function sendEvent(type, data) {
      var event = document.createEvent('Event');
      event.initEvent(type, true, true);
      for(var d in data) event[d] = data[d];
      Module['canvas'].dispatchEvent(event);
    }
    // Pass test coordinates in canvas element coordinate frame.
    var x = Module['canvas'].getBoundingClientRect().left;
    var y = Module['canvas'].getBoundingClientRect().top;

    // Test #5258: browser passing a touch event that does not contain any touches should not throw an exception from within SDL.
    sendEvent('touchstart', { touches: [ ] });

    sendEvent('touchstart', { touches: [ { pageX: x+300, pageY: y+225, deviceID: 1, identifier: 1, force: 1 } ] });
    sendEvent('touchmove', { touches: [ { pageX: x+400, pageY: y+225, deviceID: 1, identifier: 1, force: 1 } ] });
    sendEvent('touchend', { changedTouches: [ { pageX: x+400, pageY: y+225, deviceID: 1, identifier: 1, force: 1 } ] });
  );
#endif

  emscripten_set_main_loop(loop, 0, 0);

  return 0;
}