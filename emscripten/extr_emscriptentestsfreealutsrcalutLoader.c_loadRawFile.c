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
typedef  int /*<<< orphan*/  ALvoid ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutCodecLinear (int /*<<< orphan*/ *,size_t,int,int,int) ; 
 size_t _alutInputStreamGetRemainingLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _alutInputStreamRead (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static BufferData *loadRawFile(InputStream * stream)
{
  size_t length = _alutInputStreamGetRemainingLength(stream);
  ALvoid *data = _alutInputStreamRead(stream, length);

  if (data == NULL)
  {
    return NULL;
  }
  /* Guesses */
  return _alutCodecLinear(data, length, 1, 8, 8000);
}