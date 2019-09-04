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
typedef  int /*<<< orphan*/  BufferData ;
typedef  int /*<<< orphan*/  ALuint ;
typedef  int /*<<< orphan*/  ALsizei ;
typedef  scalar_t__ ALfloat ;
typedef  int /*<<< orphan*/  ALenum ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_BUFFER_DATA ; 
 int /*<<< orphan*/  AL_FALSE ; 
 scalar_t__ AL_NO_ERROR ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  _alutBufferDataGetData (int /*<<< orphan*/ *) ; 
 size_t _alutBufferDataGetLength (int /*<<< orphan*/ *) ; 
 scalar_t__ _alutBufferDataGetSampleFrequency (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutGetFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alBufferData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ alGetError () ; 

__attribute__((used)) static ALboolean passBufferData(BufferData * bufferData, ALuint bid)
{
  ALenum format;
  size_t size;
  ALfloat frequency;

  if (!_alutGetFormat(bufferData, &format))
  {
    return AL_FALSE;
  }
  /* GCC is a bit picky about casting function calls, so we do it in two
   * steps... */
  size = _alutBufferDataGetLength(bufferData);
  frequency = _alutBufferDataGetSampleFrequency(bufferData);
  alBufferData(bid, format, _alutBufferDataGetData(bufferData), (ALsizei) size, (ALsizei) frequency);
  if (alGetError() != AL_NO_ERROR)
  {
    _alutSetError(ALUT_ERROR_BUFFER_DATA);
    return AL_FALSE;
  }
  return AL_TRUE;
}