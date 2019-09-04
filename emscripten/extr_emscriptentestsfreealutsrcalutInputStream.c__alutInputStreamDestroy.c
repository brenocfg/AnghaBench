#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fileDescriptor; } ;
struct TYPE_6__ {struct TYPE_6__* fileName; TYPE_1__ u; scalar_t__ isFileStream; } ;
typedef  TYPE_2__ InputStream ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

ALboolean _alutInputStreamDestroy(InputStream * stream)
{
  ALboolean status = (stream->isFileStream && fclose(stream->u.fileDescriptor)) ? AL_FALSE : AL_TRUE;

  if (stream->fileName)
  {
    free(stream->fileName);
  }
  free(stream);
  return status;
}