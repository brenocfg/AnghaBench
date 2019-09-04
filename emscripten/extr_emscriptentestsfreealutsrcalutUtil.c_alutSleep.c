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
typedef  scalar_t__ ALuint ;
typedef  scalar_t__ ALfloat ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_INVALID_VALUE ; 
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 

ALboolean alutSleep(ALfloat duration)
{
  if (duration < 0)
  {
    _alutSetError(ALUT_ERROR_INVALID_VALUE);
    return AL_FALSE;
  }

  {
    ALuint seconds = (ALuint) duration;
    ALfloat rest = duration - (ALfloat) seconds;

#if HAVE_NANOSLEEP && HAVE_TIME_H

    ALuint microSecs = (ALuint) (rest * 1000000);
    struct timespec t, remainingTime;

    t.tv_sec = (time_t) seconds;
    t.tv_nsec = ((long)microSecs) * 1000;

    /* At least the interaction of nanosleep and signals is specified! */
    while (nanosleep(&t, &remainingTime) < 0)
    {
      if (errno != EINTR)
      {
        return AL_FALSE;
      }
      /* If we received a signal, let's try again with the remaining time. */
      t.tv_sec = remainingTime.tv_sec;
      t.tv_nsec = remainingTime.tv_nsec;
    }

#elif HAVE_USLEEP && HAVE_UNISTD_H

    while (seconds > 0)
    {
      usleep(1000000);
      seconds--;
    }
    usleep((unsigned int)(rest * 1000000));

#elif HAVE_SLEEP && HAVE_WINDOWS_H

    while (seconds > 0)
    {
      Sleep(1000);
      seconds--;
    }
    Sleep((DWORD) (rest * 1000));

#endif

  }
  return AL_TRUE;
}