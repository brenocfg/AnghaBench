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
typedef  int /*<<< orphan*/  ALuint ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_GEN_BUFFERS ; 
 int /*<<< orphan*/  AL_NONE ; 
 scalar_t__ AL_NO_ERROR ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alGenBuffers (int,int /*<<< orphan*/ *) ; 
 scalar_t__ alGetError () ; 

__attribute__((used)) static ALuint generateBuffer(void)
{
  ALuint buffer;

  alGenBuffers(1, &buffer);
  if (alGetError() != AL_NO_ERROR)
  {
    _alutSetError(ALUT_ERROR_GEN_BUFFERS);
    return AL_NONE;
  }
  return buffer;
}