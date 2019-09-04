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
 int Mix_OpenAudio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int load (char*) ; 
 int /*<<< orphan*/  pan ; 
 int play () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sound ; 

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_AUDIO);

  int ret = Mix_OpenAudio(0, 0, 0, 0); // we ignore all these..
  assert(ret == 0);

  sound = load("the_entertainer.wav");
  assert(sound);

  int channel = play();

  emscripten_set_main_loop(pan, 30, 0);

  emscripten_run_script("element = document.createElement('input');"
                        "element.setAttribute('type', 'button');"
                        "element.setAttribute('value', 'replay!');"
                        "element.setAttribute('onclick', 'Module[\"_play\"]()');"
                        "document.body.appendChild(element);");

  printf("you should hear the sound moving from left to right. press the button to replay!\n");

  return 0;
}