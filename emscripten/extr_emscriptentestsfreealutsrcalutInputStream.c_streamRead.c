#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* data; int /*<<< orphan*/  fileDescriptor; } ;
struct TYPE_5__ {size_t remainingLength; TYPE_1__ u; scalar_t__ isFileStream; } ;
typedef  TYPE_2__ InputStream ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA ; 
 int /*<<< orphan*/  ALUT_ERROR_IO_ERROR ; 
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 

__attribute__((used)) static ALboolean streamRead(InputStream * stream, void *ptr, size_t numBytesToRead)
{
  if (stream->isFileStream)
  {
    size_t numBytesRead = fread(ptr, 1, numBytesToRead, stream->u.fileDescriptor);

    if (numBytesToRead != numBytesRead)
    {
      _alutSetError(ferror(stream->u.fileDescriptor) ? ALUT_ERROR_IO_ERROR : ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA);
      return AL_FALSE;
    }
    return AL_TRUE;
  }
  else
  {
    if (stream->remainingLength < numBytesToRead)
    {
      _alutSetError(ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA);
      return AL_FALSE;
    }
    memcpy(ptr, stream->u.data, numBytesToRead);
    stream->u.data = ((const char *)(stream->u.data) + numBytesToRead);
    return AL_TRUE;
  }
}