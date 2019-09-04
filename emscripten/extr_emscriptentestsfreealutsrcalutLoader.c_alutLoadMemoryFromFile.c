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
typedef  int /*<<< orphan*/  ALsizei ;
typedef  int /*<<< orphan*/  ALfloat ;
typedef  int /*<<< orphan*/  ALenum ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutInputStreamConstructFromFile (char const*) ; 
 int /*<<< orphan*/ * _alutLoadMemoryFromInputStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutSanityCheck () ; 

ALvoid *alutLoadMemoryFromFile(const char *fileName, ALenum * format, ALsizei * size, ALfloat * frequency)
{
  InputStream *stream;

  if (!_alutSanityCheck())
  {
    return NULL;
  }
  stream = _alutInputStreamConstructFromFile(fileName);
  return _alutLoadMemoryFromInputStream(stream, format, size, frequency);
}