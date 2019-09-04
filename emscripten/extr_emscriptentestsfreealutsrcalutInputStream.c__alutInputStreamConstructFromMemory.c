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
struct TYPE_4__ {int /*<<< orphan*/  const* data; } ;
struct TYPE_5__ {size_t remainingLength; TYPE_1__ u; int /*<<< orphan*/ * fileName; int /*<<< orphan*/  isFileStream; } ;
typedef  TYPE_2__ InputStream ;
typedef  int /*<<< orphan*/  ALvoid ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 scalar_t__ _alutMalloc (int) ; 

InputStream *_alutInputStreamConstructFromMemory(const ALvoid * data, size_t length)
{
  InputStream *stream = (InputStream *) _alutMalloc(sizeof(InputStream));

  if (stream == NULL)
  {
    return NULL;
  }

  stream->isFileStream = AL_FALSE;
  stream->fileName = NULL;
  stream->remainingLength = length;
  stream->u.data = data;
  return stream;
}