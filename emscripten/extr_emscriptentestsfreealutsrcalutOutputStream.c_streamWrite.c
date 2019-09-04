#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t maximumLength; size_t current; } ;
typedef  TYPE_1__ OutputStream ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_IO_ERROR ; 
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 size_t _alutOutputStreamGetLength (TYPE_1__*) ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 

__attribute__((used)) static ALboolean streamWrite(OutputStream * stream, const void *ptr, size_t numBytesToWrite)
{
  size_t remainingLength = stream->maximumLength - _alutOutputStreamGetLength(stream);

  if (remainingLength < numBytesToWrite)
  {
    /* this should never happen within our library */
    _alutSetError(ALUT_ERROR_IO_ERROR);
    return AL_FALSE;
  }
  memcpy(stream->current, ptr, numBytesToWrite);
  stream->current += numBytesToWrite;
  return AL_TRUE;
}