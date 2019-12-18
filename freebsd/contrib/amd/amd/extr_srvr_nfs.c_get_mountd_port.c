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
typedef  scalar_t__ wchan_t ;
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_7__ {int np_error; int np_mountd_inval; int /*<<< orphan*/  np_mountd; } ;
typedef  TYPE_1__ nfs_private ;
struct TYPE_8__ {int fs_flags; scalar_t__ fs_private; } ;
typedef  TYPE_2__ fserver ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int FSF_WANT ; 
 scalar_t__ FSRV_ISDOWN (TYPE_2__*) ; 
 scalar_t__ FSRV_ISUP (TYPE_2__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  recompute_portmap (TYPE_2__*) ; 
 int /*<<< orphan*/  sched_task (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wakeup_task ; 

int
get_mountd_port(fserver *fs, u_short *port, wchan_t wchan)
{
  int error = -1;

  if (FSRV_ISDOWN(fs))
    return EWOULDBLOCK;

  if (FSRV_ISUP(fs)) {
    nfs_private *np = (nfs_private *) fs->fs_private;
    if (np->np_error == 0) {
      *port = np->np_mountd;
      error = 0;
    } else {
      error = np->np_error;
    }
    /*
     * Now go get the port mapping again in case it changed.
     * Note that it is used even if (np_mountd_inval)
     * is True.  The flag is used simply as an
     * indication that the mountd may be invalid, not
     * that it is known to be invalid.
     */
    switch (np->np_mountd_inval) {
    case 'Y':
      recompute_portmap(fs);
      break;
    case 'N':
      np->np_mountd_inval = 'Y';
      break;
    case 'P':
      break;
    default:
      abort();
    }
  }
  if (error < 0 && wchan && !(fs->fs_flags & FSF_WANT)) {
    /*
     * If a wait channel is supplied, and no
     * error has yet occurred, then arrange
     * that a wakeup is done on the wait channel,
     * whenever a wakeup is done on this fs node.
     * Wakeup's are done on the fs node whenever
     * it changes state - thus causing control to
     * come back here and new, better things to happen.
     */
    fs->fs_flags |= FSF_WANT;
    sched_task(wakeup_task, wchan, (wchan_t) fs);
  }
  return error;
}