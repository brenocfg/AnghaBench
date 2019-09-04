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
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  still_running; int /*<<< orphan*/  buffer_pos; TYPE_1__ handle; } ;
typedef  TYPE_2__ URL_FILE ;

/* Variables and functions */
#define  CFTYPE_CURL 129 
#define  CFTYPE_FILE 128 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  errno ; 
 int feof (int /*<<< orphan*/ ) ; 

int url_feof(URL_FILE *file)
{
  int ret = 0;

  switch(file->type) {
  case CFTYPE_FILE:
    ret = feof(file->handle.file);
    break;

  case CFTYPE_CURL:
    if((file->buffer_pos == 0) && (!file->still_running))
      ret = 1;
    break;

  default: /* unknown or supported type - oh dear */
    ret = -1;
    errno = EBADF;
    break;
  }
  return ret;
}