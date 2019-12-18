#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* voidp ;
struct TYPE_7__ {scalar_t__ fs_refc; int fs_flags; struct TYPE_7__* fs_host; struct TYPE_7__* fs_ip; scalar_t__ fs_private; int /*<<< orphan*/  (* fs_prfree ) (scalar_t__) ;int /*<<< orphan*/  fs_q; } ;
typedef  TYPE_1__ fserver ;

/* Variables and functions */
 int FSF_WANT ; 
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 
 int /*<<< orphan*/  dlog (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  rem_que (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  wakeup_srvr (TYPE_1__*) ; 

__attribute__((used)) static void
timeout_srvr(voidp v)
{
  fserver *fs = v;

  /*
   * If the reference count is still zero then
   * we are free to remove this node
   */
  if (fs->fs_refc == 0) {
    dlog("Deleting file server %s", fs->fs_host);
    if (fs->fs_flags & FSF_WANT)
      wakeup_srvr(fs);

    /*
     * Remove from queue.
     */
    rem_que(&fs->fs_q);
    /*
     * (Possibly) call the private free routine.
     */
    if (fs->fs_private && fs->fs_prfree)
      (*fs->fs_prfree) (fs->fs_private);

    /*
     * Free the net address
     */
    XFREE(fs->fs_ip);

    /*
     * Free the host name.
     */
    XFREE(fs->fs_host);

    /*
     * Discard the fserver object.
     */
    XFREE(fs);
  }
}