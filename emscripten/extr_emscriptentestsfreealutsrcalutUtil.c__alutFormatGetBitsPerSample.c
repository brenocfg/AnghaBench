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
typedef  int ALint ;
typedef  int ALenum ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
#define  AL_FORMAT_MONO16 131 
#define  AL_FORMAT_MONO8 130 
#define  AL_FORMAT_STEREO16 129 
#define  AL_FORMAT_STEREO8 128 
 int /*<<< orphan*/  AL_TRUE ; 

ALboolean _alutFormatGetBitsPerSample(ALenum format, ALint * bitsPerSample)
{
  switch (format)
  {
  case AL_FORMAT_MONO8:
  case AL_FORMAT_STEREO8:
    *bitsPerSample = 8;
    return AL_TRUE;
  case AL_FORMAT_MONO16:
  case AL_FORMAT_STEREO16:
    *bitsPerSample = 16;
    return AL_TRUE;
  }
  return AL_FALSE;
}