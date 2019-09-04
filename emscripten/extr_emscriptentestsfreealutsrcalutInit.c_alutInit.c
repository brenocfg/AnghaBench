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
typedef  int /*<<< orphan*/  ALCcontext ;

/* Variables and functions */
 scalar_t__ ALUTDeviceAndContext ; 
 int /*<<< orphan*/  ALUT_ERROR_CREATE_CONTEXT ; 
 int /*<<< orphan*/  ALUT_ERROR_INVALID_OPERATION ; 
 int /*<<< orphan*/  ALUT_ERROR_INVALID_VALUE ; 
 int /*<<< orphan*/  ALUT_ERROR_MAKE_CONTEXT_CURRENT ; 
 int /*<<< orphan*/  ALUT_ERROR_OPEN_DEVICE ; 
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 scalar_t__ Unintialized ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCloseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcCreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcDestroyContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcOpenDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alutContext ; 
 scalar_t__ initialisationState ; 

ALboolean alutInit(int *argcp, char **argv)
{
  ALCdevice *device;
  ALCcontext *context;

  if (initialisationState != Unintialized)
  {
    _alutSetError(ALUT_ERROR_INVALID_OPERATION);
    return AL_FALSE;
  }

  if ((argcp == NULL) != (argv == NULL))
  {
    _alutSetError(ALUT_ERROR_INVALID_VALUE);
    return AL_FALSE;
  }

  device = alcOpenDevice(NULL);
  if (device == NULL)
  {
    _alutSetError(ALUT_ERROR_OPEN_DEVICE);
    return AL_FALSE;
  }

  context = alcCreateContext(device, NULL);
  if (context == NULL)
  {
    alcCloseDevice(device);
    _alutSetError(ALUT_ERROR_CREATE_CONTEXT);
    return AL_FALSE;
  }

  if (!alcMakeContextCurrent(context))
  {
    alcDestroyContext(context);
    alcCloseDevice(device);
    _alutSetError(ALUT_ERROR_MAKE_CONTEXT_CURRENT);
    return AL_FALSE;
  }

  initialisationState = ALUTDeviceAndContext;
  alutContext = context;
  return AL_TRUE;
}