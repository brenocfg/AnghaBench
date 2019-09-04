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

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_INVALID_OPERATION ; 
 int /*<<< orphan*/  ALUT_ERROR_INVALID_VALUE ; 
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 scalar_t__ ExternalDeviceAndContext ; 
 scalar_t__ Unintialized ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 scalar_t__ initialisationState ; 

ALboolean alutInitWithoutContext(int *argcp, char **argv)
{
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

  initialisationState = ExternalDeviceAndContext;
  return AL_TRUE;
}