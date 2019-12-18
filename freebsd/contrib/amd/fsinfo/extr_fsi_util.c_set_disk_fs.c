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
struct TYPE_4__ {int /*<<< orphan*/  m_q; } ;
typedef  TYPE_1__ fsi_mount ;
struct TYPE_5__ {int d_mask; char* d_fstype; char* d_opts; char* d_dumpset; char* d_log; int /*<<< orphan*/ * d_mount; void* d_freq; void* d_passno; } ;
typedef  TYPE_2__ disk_fs ;

/* Variables and functions */
#define  DF_DUMPSET 134 
#define  DF_FREQ 133 
#define  DF_FSTYPE 132 
#define  DF_LOG 131 
#define  DF_MOUNT 130 
#define  DF_OPTS 129 
#define  DF_PASSNO 128 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  abort () ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/ * disk_fs_strings ; 
 int /*<<< orphan*/  fsi_error (char*,int /*<<< orphan*/ ) ; 

void
set_disk_fs(disk_fs *dp, int k, char *v)
{
  int m = 1 << k;

  if (dp->d_mask & m) {
    fsi_error("fs field \"%s\" already set", disk_fs_strings[k]);
    return;
  }
  dp->d_mask |= m;

  switch (k) {

  case DF_FSTYPE:
    dp->d_fstype = v;
    break;

  case DF_OPTS:
    dp->d_opts = v;
    break;

  case DF_DUMPSET:
    dp->d_dumpset = v;
    break;

  case DF_LOG:
    dp->d_log = v;
    break;

  case DF_PASSNO:
    dp->d_passno = atoi(v);
    XFREE(v);
    break;

  case DF_FREQ:
    dp->d_freq = atoi(v);
    XFREE(v);
    break;

  case DF_MOUNT:
    dp->d_mount = &((fsi_mount *) v)->m_q;
    break;

  default:
    abort();
    break;
  }
}