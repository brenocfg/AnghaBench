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
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 scalar_t__ _alutMalloc (size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  streamRead (int /*<<< orphan*/ *,char*,size_t) ; 

ALboolean _alutInputStreamSkip(InputStream * stream, size_t numBytesToSkip)
{
  ALboolean status;
  char *buf;

  if (numBytesToSkip == 0)
  {
    return AL_TRUE;
  }
  buf = (char *)_alutMalloc(numBytesToSkip);
  if (buf == NULL)
  {
    return AL_FALSE;
  }
  status = streamRead(stream, buf, numBytesToSkip);
  free(buf);
  return status;
}