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
typedef  int /*<<< orphan*/  SDL_Joystick ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 scalar_t__ SDL_DISABLE ; 
 scalar_t__ SDL_ENABLE ; 
 int /*<<< orphan*/  SDL_JOYAXISMOTION ; 
 int /*<<< orphan*/  SDL_JOYBUTTONDOWN ; 
 int /*<<< orphan*/  SDL_JOYBUTTONUP ; 
 int /*<<< orphan*/  SDL_JoystickClose (int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_JoystickEventState (scalar_t__) ; 
 int SDL_JoystickGetAxis (int /*<<< orphan*/ *,int) ; 
 int SDL_JoystickGetButton (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SDL_JoystickIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_JoystickName (int) ; 
 int SDL_JoystickNumAxes (int /*<<< orphan*/ *) ; 
 int SDL_JoystickNumButtons (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SDL_JoystickOpen (int /*<<< orphan*/ ) ; 
 int SDL_JoystickOpened (int) ; 
 int /*<<< orphan*/  SDL_JoystickUpdate () ; 
 int SDL_NumJoysticks () ; 
 int SDL_PRESSED ; 
 scalar_t__ SDL_QUERY ; 
 int SDL_RELEASED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertJoystickEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assertNoJoystickEvent () ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void main_2(void* arg) {
  // TODO: At the moment, we only support joystick support through polling.
  emscripten_run_script("window.addNewGamepad('Pad Thai', 4, 16)");
  emscripten_run_script("window.addNewGamepad('Pad Kee Mao', 0, 4)");
  // Check that the joysticks exist properly.
  assert(SDL_NumJoysticks() == 2);
  assert(!SDL_JoystickOpened(0));
  assert(!SDL_JoystickOpened(1));
  SDL_Joystick* pad1 = SDL_JoystickOpen(0);
  assert(SDL_JoystickOpened(0));
  assert(SDL_JoystickIndex(pad1) == 0);
  assert(strncmp(SDL_JoystickName(0), "Pad Thai", 9) == 0);
  assert(strncmp(SDL_JoystickName(1), "Pad Kee Mao", 12) == 0);
  assert(SDL_JoystickNumAxes(pad1) == 4);
  assert(SDL_JoystickNumButtons(pad1) == 16);

  // By default, SDL will automatically process events. Test this behavior, and then disable it.
  assert(SDL_JoystickEventState(SDL_QUERY) == SDL_ENABLE);
  SDL_JoystickEventState(SDL_DISABLE);
  assert(SDL_JoystickEventState(SDL_QUERY) == SDL_DISABLE);
  // Button events.
  emscripten_run_script("window.simulateGamepadButtonDown(0, 1)");
  // We didn't tell SDL to automatically update this joystick's state.
  assertNoJoystickEvent();
  SDL_JoystickUpdate();
  assertJoystickEvent(0, SDL_JOYBUTTONDOWN, 1, SDL_PRESSED);
  assert(SDL_JoystickGetButton(pad1, 1) == 1);
  // Enable automatic updates.
  SDL_JoystickEventState(SDL_ENABLE);
  assert(SDL_JoystickEventState(SDL_QUERY) == SDL_ENABLE);
  emscripten_run_script("window.simulateGamepadButtonUp(0, 1)");
  assertJoystickEvent(0, SDL_JOYBUTTONUP, 1, SDL_RELEASED);
  assert(SDL_JoystickGetButton(pad1, 1) == 0);
  // No button change: Should not result in a new event.
  emscripten_run_script("window.simulateGamepadButtonUp(0, 1)");
  assertNoJoystickEvent();
  // Joystick 1 is not opened; should not result in a new event.
  emscripten_run_script("window.simulateGamepadButtonDown(1, 1)");
  assertNoJoystickEvent();

  // Joystick wiggling
  emscripten_run_script("window.simulateAxisMotion(0, 0, 1)");
  assertJoystickEvent(0, SDL_JOYAXISMOTION, 0, 32767);
  assert(SDL_JoystickGetAxis(pad1, 0) == 32767);
  emscripten_run_script("window.simulateAxisMotion(0, 0, 0)");
  assertJoystickEvent(0, SDL_JOYAXISMOTION, 0, 0);
  assert(SDL_JoystickGetAxis(pad1, 0) == 0);
  emscripten_run_script("window.simulateAxisMotion(0, 1, -1)");
  assertJoystickEvent(0, SDL_JOYAXISMOTION, 1, -32768);
  assert(SDL_JoystickGetAxis(pad1, 1) == -32768);
  emscripten_run_script("window.simulateAxisMotion(0, 1, -1)");
  // No joystick change: Should not result in a new event.
  assertNoJoystickEvent();
  // Joystick 1 is not opened; should not result in a new event.
  emscripten_run_script("window.simulateAxisMotion(1, 1, -1)");
  assertNoJoystickEvent();

  SDL_JoystickClose(pad1);
  assert(!SDL_JoystickOpened(0));

  // Joystick 0 is closed; we should not process any new gamepad events from it.
  emscripten_run_script("window.simulateGamepadButtonDown(0, 1)");
  assertNoJoystickEvent();

  // End test.
  printf("Test passed!\n");
  REPORT_RESULT(2);
}