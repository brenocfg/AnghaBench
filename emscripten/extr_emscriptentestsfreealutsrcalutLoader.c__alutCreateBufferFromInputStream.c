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
typedef  int /*<<< orphan*/  ALuint ;

/* Variables and functions */
 int /*<<< orphan*/  AL_NONE ; 
 int /*<<< orphan*/  _alutBufferDataDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutInputStreamDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutPassBufferData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * loadFile (int /*<<< orphan*/ *) ; 

ALuint _alutCreateBufferFromInputStream(InputStream * stream)
{
  BufferData *bufferData;
  ALuint buffer;

  if (stream == NULL)
  {
    return AL_NONE;
  }

  bufferData = loadFile(stream);
  _alutInputStreamDestroy(stream);
  if (bufferData == NULL)
  {
    return AL_NONE;
  }

  buffer = _alutPassBufferData(bufferData);
  _alutBufferDataDestroy(bufferData);

  return buffer;
}