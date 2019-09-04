#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  st_size; } ;
typedef  TYPE_2__ structStat ;
struct TYPE_7__ {int /*<<< orphan*/ * fileDescriptor; } ;
struct TYPE_9__ {TYPE_1__ u; int /*<<< orphan*/  remainingLength; int /*<<< orphan*/  fileName; int /*<<< orphan*/  isFileStream; } ;
typedef  TYPE_3__ InputStream ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_IO_ERROR ; 
 int /*<<< orphan*/  AL_TRUE ; 
 scalar_t__ _alutMalloc (int) ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ stat (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

InputStream *_alutInputStreamConstructFromFile(const char *fileName)
{
  InputStream *stream;
  structStat statBuf;
  FILE *fileDescriptor;
  char *fileNameBuffer;

  stream = (InputStream *) _alutMalloc(sizeof(InputStream));
  if (stream == NULL)
  {
    return NULL;
  }

  if (stat(fileName, &statBuf))
  {
    _alutSetError(ALUT_ERROR_IO_ERROR);
    free(stream);
    return NULL;
  }

  fileDescriptor = fopen(fileName, "rb");
  if (fileDescriptor == NULL)
  {
    _alutSetError(ALUT_ERROR_IO_ERROR);
    free(stream);
    return NULL;
  }

  fileNameBuffer = (char *)_alutMalloc(strlen(fileName) + 1);
  if (fileNameBuffer == NULL)
  {
    free(stream);
    return NULL;
  }

  stream->isFileStream = AL_TRUE;
  stream->fileName = strcpy(fileNameBuffer, fileName);
  stream->remainingLength = statBuf.st_size;
  stream->u.fileDescriptor = fileDescriptor;
  return stream;
}