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
struct TYPE_4__ {int /*<<< orphan*/  fileDescriptor; } ;
struct TYPE_5__ {scalar_t__ remainingLength; TYPE_1__ u; scalar_t__ isFileStream; } ;
typedef  TYPE_2__ InputStream ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int EOF ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

ALboolean _alutInputStreamEOF(InputStream * stream)
{
  if (stream->isFileStream)
  {
    int c = fgetc(stream->u.fileDescriptor);

    if (c != EOF)
    {
      ungetc(c, stream->u.fileDescriptor);
    }
    return (c == EOF) ? AL_TRUE : AL_FALSE;
  }
  else
  {
    return (stream->remainingLength == 0) ? AL_TRUE : AL_FALSE;
  }
}