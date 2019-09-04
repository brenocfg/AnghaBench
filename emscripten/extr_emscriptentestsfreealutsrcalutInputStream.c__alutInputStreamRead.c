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

/* Variables and functions */
 int /*<<< orphan*/ * _alutMalloc (size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

ALvoid *_alutInputStreamRead(InputStream * stream, size_t length)
{
  ALvoid *data = _alutMalloc(length);

  if (data == NULL)
  {
    return NULL;
  }

  if (!streamRead(stream, data, length))
  {
    free(data);
    return NULL;
  }

  return data;
}