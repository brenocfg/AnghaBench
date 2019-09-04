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
typedef  int /*<<< orphan*/  ALenum ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE ; 
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  _alutFormatConstruct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getBitsPerSample (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  getNumChannels (int /*<<< orphan*/  const*) ; 

ALboolean _alutGetFormat(const BufferData * bufferData, ALenum * format)
{
  if (!_alutFormatConstruct(getNumChannels(bufferData), getBitsPerSample(bufferData), format))
  {
    _alutSetError(ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE);
    return AL_FALSE;
  }
  return AL_TRUE;
}