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
typedef  int /*<<< orphan*/  BufferData ;
typedef  scalar_t__ ALsizei ;
typedef  int /*<<< orphan*/  ALfloat ;
typedef  int /*<<< orphan*/  ALenum ;

/* Variables and functions */
 int /*<<< orphan*/  _alutBufferDataDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutBufferDataDetachData (int /*<<< orphan*/ *) ; 
 void* _alutBufferDataGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ _alutBufferDataGetLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutBufferDataGetSampleFrequency (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutGetFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutInputStreamDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * loadFile (int /*<<< orphan*/ *) ; 

void *_alutLoadMemoryFromInputStream(InputStream * stream, ALenum * format, ALsizei * size, ALfloat * frequency)
{
  BufferData *bufferData;
  ALenum fmt;
  void *data;

  if (stream == NULL)
  {
    return NULL;
  }

  bufferData = loadFile(stream);
  if (bufferData == NULL)
  {
    _alutInputStreamDestroy(stream);
    return NULL;
  }
  _alutInputStreamDestroy(stream);

  if (!_alutGetFormat(bufferData, &fmt))
  {
    _alutBufferDataDestroy(bufferData);
    return NULL;
  }

  if (size != NULL)
  {
    *size = (ALsizei) _alutBufferDataGetLength(bufferData);
  }

  if (format != NULL)
  {
    *format = fmt;
  }

  if (frequency != NULL)
  {
    *frequency = _alutBufferDataGetSampleFrequency(bufferData);
  }

  data = _alutBufferDataGetData(bufferData);
  _alutBufferDataDetachData(bufferData);
  _alutBufferDataDestroy(bufferData);
  return data;
}