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
typedef  int /*<<< orphan*/  ALenum ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_FORMAT_MONO16 ; 
 int /*<<< orphan*/  AL_FORMAT_MONO8 ; 
 int /*<<< orphan*/  AL_FORMAT_STEREO16 ; 
 int /*<<< orphan*/  AL_FORMAT_STEREO8 ; 
 int /*<<< orphan*/  AL_TRUE ; 

ALboolean _alutFormatConstruct(ALint numChannels, ALint bitsPerSample, ALenum * format)
{
  switch (numChannels)
  {
  case 1:
    switch (bitsPerSample)
    {
    case 8:
      *format = AL_FORMAT_MONO8;
      return AL_TRUE;
    case 16:
      *format = AL_FORMAT_MONO16;
      return AL_TRUE;
    }
    break;
  case 2:
    switch (bitsPerSample)
    {
    case 8:
      *format = AL_FORMAT_STEREO8;
      return AL_TRUE;
    case 16:
      *format = AL_FORMAT_STEREO16;
      return AL_TRUE;
    }
    break;
  }
  return AL_FALSE;
}