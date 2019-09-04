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
typedef  int /*<<< orphan*/  InputStream ;
typedef  scalar_t__ ALsizei ;
typedef  scalar_t__ ALfloat ;
typedef  int /*<<< orphan*/  ALenum ;
typedef  int /*<<< orphan*/  ALbyte ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/ * _alutInputStreamConstructFromMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _alutLoadMemoryFromInputStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

void alutLoadWAVMemory(ALbyte * buffer, ALenum * format, void **data, ALsizei * size, ALsizei * frequency
#if !defined(__APPLE__)
                       , ALboolean * loop
#endif
  )
{
  InputStream *stream;
  ALfloat freq;

  /* Don't do an _alutSanityCheck () because it's not required in ALUT 0.x.x */

  /* ToDo: Can we do something less insane than passing 0x7FFFFFFF? */
  stream = _alutInputStreamConstructFromMemory(buffer, 0x7FFFFFFF);
  _alutLoadMemoryFromInputStream(stream, format, size, &freq);
  if (*data == NULL)
  {
    return;
  }

  if (frequency)
  {
    *frequency = (ALsizei) freq;
  }

#if !defined(__APPLE__)
  if (loop)
  {
    *loop = AL_FALSE;
  }
#endif
}