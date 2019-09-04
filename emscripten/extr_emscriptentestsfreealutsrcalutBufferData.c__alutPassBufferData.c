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
typedef  scalar_t__ ALuint ;

/* Variables and functions */
 scalar_t__ AL_NONE ; 
 scalar_t__ generateBuffer () ; 
 int /*<<< orphan*/  passBufferData (int /*<<< orphan*/ *,scalar_t__) ; 

ALuint _alutPassBufferData(BufferData * bufferData)
{
  ALuint buffer = generateBuffer();

  if (buffer == AL_NONE)
  {
    return AL_NONE;
  }

  if (!passBufferData(bufferData, buffer))
  {
    return AL_NONE;
  }

  return buffer;
}