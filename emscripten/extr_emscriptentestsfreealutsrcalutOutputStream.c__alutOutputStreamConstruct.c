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
struct TYPE_4__ {size_t maximumLength; int /*<<< orphan*/ * data; int /*<<< orphan*/ * current; } ;
typedef  TYPE_1__ OutputStream ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutMalloc (size_t) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

OutputStream *_alutOutputStreamConstruct(size_t maximumLength)
{
  OutputStream *stream = (OutputStream *) _alutMalloc(sizeof(OutputStream));

  if (stream == NULL)
  {
    return NULL;
  }
  stream->data = _alutMalloc(maximumLength);
  if (stream->data == NULL)
  {
    free(stream);
    return NULL;
  }
  stream->current = stream->data;
  stream->maximumLength = maximumLength;
  return stream;
}