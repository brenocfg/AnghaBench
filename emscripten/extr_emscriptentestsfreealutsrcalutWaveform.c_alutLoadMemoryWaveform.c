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
typedef  int /*<<< orphan*/  OutputStream ;
typedef  int /*<<< orphan*/  InputStream ;
typedef  int /*<<< orphan*/  ALvoid ;
typedef  int /*<<< orphan*/  ALsizei ;
typedef  int /*<<< orphan*/  ALfloat ;
typedef  int /*<<< orphan*/  ALenum ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutInputStreamConstructFromMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _alutLoadMemoryFromInputStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutOutputStreamDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutOutputStreamGetData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutOutputStreamGetLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutSanityCheck () ; 
 int /*<<< orphan*/ * generateWaveform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ALvoid *alutLoadMemoryWaveform(ALenum waveshape, ALfloat frequency, ALfloat phase, ALfloat duration, ALenum * format, ALsizei * size, ALfloat * freq)
{
  OutputStream *outputStream;
  InputStream *inputStream;
  ALvoid *data;

  if (!_alutSanityCheck())
  {
    return NULL;
  }

  outputStream = generateWaveform(waveshape, frequency, phase, duration);
  if (outputStream == NULL)
  {
    return NULL;
  }

  /* We could do something more efficient here if the internal stream
   * structures were known, but this would break the abstraction. */
  inputStream = _alutInputStreamConstructFromMemory(_alutOutputStreamGetData(outputStream), _alutOutputStreamGetLength(outputStream));
  if (inputStream == NULL)
  {
    _alutOutputStreamDestroy(outputStream);
    return NULL;
  }

  data = _alutLoadMemoryFromInputStream(inputStream, format, size, freq);
  _alutOutputStreamDestroy(outputStream);
  return data;
}