#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; TYPE_3__* param; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ pm_file ;
typedef  int /*<<< orphan*/  gzFile ;
struct TYPE_5__ {int /*<<< orphan*/  total_bytes; } ;
struct TYPE_7__ {long fpos_out; TYPE_1__ header; } ;
typedef  TYPE_3__ cso_struct ;

/* Variables and functions */
 scalar_t__ PMT_CSO ; 
 scalar_t__ PMT_UNCOMPRESSED ; 
 scalar_t__ PMT_ZIP ; 
 int /*<<< orphan*/  PicoMessage (char*) ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int) ; 
 int ftell (int /*<<< orphan*/ ) ; 
 int gzseek (int /*<<< orphan*/ ,long,int) ; 
 long gztell (int /*<<< orphan*/ ) ; 

int pm_seek(pm_file *stream, long offset, int whence)
{
  if (stream->type == PMT_UNCOMPRESSED)
  {
    fseek(stream->file, offset, whence);
    return ftell(stream->file);
  }
  else if (stream->type == PMT_ZIP)
  {
    if (PicoMessage != NULL && offset > 6*1024*1024) {
      long pos = gztell((gzFile) stream->param);
      if (offset < pos || offset - pos > 6*1024*1024)
        PicoMessage("Decompressing data...");
    }
    return gzseek((gzFile) stream->param, offset, whence);
  }
  else if (stream->type == PMT_CSO)
  {
    cso_struct *cso = stream->param;
    switch (whence)
    {
      case SEEK_CUR: cso->fpos_out += offset; break;
      case SEEK_SET: cso->fpos_out  = offset; break;
      case SEEK_END: cso->fpos_out  = cso->header.total_bytes - offset; break;
    }
    return cso->fpos_out;
  }
  else
    return -1;
}