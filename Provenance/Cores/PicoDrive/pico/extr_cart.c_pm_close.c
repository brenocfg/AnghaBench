#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; TYPE_2__* file; struct TYPE_7__* param; } ;
typedef  TYPE_1__ pm_file ;
typedef  int /*<<< orphan*/  gzFile ;
struct TYPE_8__ {int /*<<< orphan*/ * fp; } ;
typedef  TYPE_2__ ZIP ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ PMT_CSO ; 
 scalar_t__ PMT_UNCOMPRESSED ; 
 scalar_t__ PMT_ZIP ; 
 int /*<<< orphan*/  closezip (TYPE_2__*) ; 
 int /*<<< orphan*/  fclose (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ ) ; 

int pm_close(pm_file *fp)
{
  int ret = 0;

  if (fp == NULL) return EOF;

  if (fp->type == PMT_UNCOMPRESSED)
  {
    fclose(fp->file);
  }
  else if (fp->type == PMT_ZIP)
  {
    ZIP *zipfile = fp->file;
    gzclose((gzFile) fp->param);
    zipfile->fp = NULL; // gzclose() closed it
    closezip(zipfile);
  }
  else if (fp->type == PMT_CSO)
  {
    free(fp->param);
    fclose(fp->file);
  }
  else
    ret = EOF;

  free(fp);
  return ret;
}