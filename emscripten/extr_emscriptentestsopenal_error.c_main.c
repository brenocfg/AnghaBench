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
 scalar_t__ ALC_INVALID_ENUM ; 
 scalar_t__ ALC_NO_ERROR ; 
 scalar_t__ AL_INVALID_ENUM ; 
 scalar_t__ AL_NO_ERROR ; 
 scalar_t__ alGetError () ; 
 int /*<<< orphan*/  alGetFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCloseDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alcCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcDestroyContext (int /*<<< orphan*/ *) ; 
 scalar_t__ alcGetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcGetIntegerv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  alcMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcOpenDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * context ; 
 int /*<<< orphan*/  device ; 

int main(int argc, char* argv[]) {
  //
  // Setup the AL context.
  //
  device = alcOpenDevice(NULL);

  // Request an invalid enum to generate an ALC error
  int value = 0;
  alcGetIntegerv(device, 0, 1, &value);
  assert(alcGetError(device) == ALC_INVALID_ENUM);
  // Check that the error is reset after reading it.
  assert(alcGetError(device) == ALC_NO_ERROR);

  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);

  // Request an invalid enum to generate an AL error
  alGetFloat(0);
  assert(alGetError() == AL_INVALID_ENUM);
  // Check that the error is reset after reading it.
  assert(alGetError() == AL_NO_ERROR);

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

#ifdef __EMSCRIPTEN__
    REPORT_RESULT(1);
#endif
}