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
typedef  int /*<<< orphan*/  ALuint ;

/* Variables and functions */
 int /*<<< orphan*/  AL_NONE ; 
 int /*<<< orphan*/  _alutCreateBufferFromInputStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _alutInputStreamConstructFromFile (char const*) ; 
 int /*<<< orphan*/  _alutSanityCheck () ; 

ALuint alutCreateBufferFromFile(const char *fileName)
{
  InputStream *stream;

  if (!_alutSanityCheck())
  {
    return AL_NONE;
  }
  stream = _alutInputStreamConstructFromFile(fileName);
  return _alutCreateBufferFromInputStream(stream);
}