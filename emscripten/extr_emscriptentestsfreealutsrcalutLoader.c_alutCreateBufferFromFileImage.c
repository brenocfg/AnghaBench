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
typedef  int /*<<< orphan*/  ALvoid ;
typedef  int /*<<< orphan*/  ALuint ;
typedef  int /*<<< orphan*/  ALsizei ;

/* Variables and functions */
 int /*<<< orphan*/  AL_NONE ; 
 int /*<<< orphan*/  _alutCreateBufferFromInputStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _alutInputStreamConstructFromMemory (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _alutSanityCheck () ; 

ALuint alutCreateBufferFromFileImage(const ALvoid * data, ALsizei length)
{
  InputStream *stream;

  if (!_alutSanityCheck())
  {
    return AL_NONE;
  }
  stream = _alutInputStreamConstructFromMemory(data, length);
  return _alutCreateBufferFromInputStream(stream);
}