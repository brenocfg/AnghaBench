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
typedef  int /*<<< orphan*/  ALCcontext ;

/* Variables and functions */
 scalar_t__ ALC_NO_ERROR ; 
 int /*<<< orphan*/  ALUT_ERROR_ALC_ERROR_ON_ENTRY ; 
 int /*<<< orphan*/  ALUT_ERROR_AL_ERROR_ON_ENTRY ; 
 int /*<<< orphan*/  ALUT_ERROR_INVALID_OPERATION ; 
 int /*<<< orphan*/  ALUT_ERROR_NO_CURRENT_CONTEXT ; 
 int /*<<< orphan*/  AL_FALSE ; 
 scalar_t__ AL_NO_ERROR ; 
 int /*<<< orphan*/  AL_TRUE ; 
 scalar_t__ Unintialized ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 scalar_t__ alGetError () ; 
 int /*<<< orphan*/  alcGetContextsDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcGetCurrentContext () ; 
 scalar_t__ alcGetError (int /*<<< orphan*/ ) ; 
 scalar_t__ initialisationState ; 

ALboolean _alutSanityCheck(void)
{
  ALCcontext *context;

  if (initialisationState == Unintialized)
  {
    _alutSetError(ALUT_ERROR_INVALID_OPERATION);
    return AL_FALSE;
  }

  context = alcGetCurrentContext();
  if (context == NULL)
  {
    _alutSetError(ALUT_ERROR_NO_CURRENT_CONTEXT);
    return AL_FALSE;
  }

  if (alGetError() != AL_NO_ERROR)
  {
    _alutSetError(ALUT_ERROR_AL_ERROR_ON_ENTRY);
    return AL_FALSE;
  }

  if (alcGetError(alcGetContextsDevice(context)) != ALC_NO_ERROR)
  {
    _alutSetError(ALUT_ERROR_ALC_ERROR_ON_ENTRY);
    return AL_FALSE;
  }

  return AL_TRUE;
}