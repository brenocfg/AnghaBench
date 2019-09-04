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
typedef  int /*<<< orphan*/  ALboolean ;
typedef  int /*<<< orphan*/  ALCdevice ;

/* Variables and functions */
 scalar_t__ ALC_NO_ERROR ; 
 int /*<<< orphan*/  ALUT_ERROR_CLOSE_DEVICE ; 
 int /*<<< orphan*/  ALUT_ERROR_DESTROY_CONTEXT ; 
 int /*<<< orphan*/  ALUT_ERROR_INVALID_OPERATION ; 
 int /*<<< orphan*/  ALUT_ERROR_MAKE_CONTEXT_CURRENT ; 
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 scalar_t__ ExternalDeviceAndContext ; 
 scalar_t__ Unintialized ; 
 int /*<<< orphan*/  _alutSanityCheck () ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCloseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcDestroyContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alcGetContextsDevice (int /*<<< orphan*/ ) ; 
 scalar_t__ alcGetError (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alutContext ; 
 scalar_t__ initialisationState ; 

ALboolean alutExit(void)
{
  ALCdevice *device;

  if (initialisationState == Unintialized)
  {
    _alutSetError(ALUT_ERROR_INVALID_OPERATION);
    return AL_FALSE;
  }

  if (initialisationState == ExternalDeviceAndContext)
  {
    initialisationState = Unintialized;
    return AL_TRUE;
  }

  if (!_alutSanityCheck())
  {
    return AL_FALSE;
  }

  if (!alcMakeContextCurrent(NULL))
  {
    _alutSetError(ALUT_ERROR_MAKE_CONTEXT_CURRENT);
    return AL_FALSE;
  }

  device = alcGetContextsDevice(alutContext);
  alcDestroyContext(alutContext);
  if (alcGetError(device) != ALC_NO_ERROR)
  {
    _alutSetError(ALUT_ERROR_DESTROY_CONTEXT);
    return AL_FALSE;
  }

  if (!alcCloseDevice(device))
  {
    _alutSetError(ALUT_ERROR_CLOSE_DEVICE);
    return AL_FALSE;
  }

  initialisationState = Unintialized;
  return AL_TRUE;
}