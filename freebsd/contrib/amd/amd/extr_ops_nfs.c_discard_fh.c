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
typedef  scalar_t__ opaque_t ;
struct TYPE_5__ {struct TYPE_5__* fh_path; TYPE_2__* fh_fs; int /*<<< orphan*/  fh_q; } ;
typedef  TYPE_1__ fh_cache ;
struct TYPE_6__ {int /*<<< orphan*/  fs_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free_srvr (TYPE_2__*) ; 
 int /*<<< orphan*/  rem_que (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
discard_fh(opaque_t arg)
{
  fh_cache *fp = (fh_cache *) arg;

  rem_que(&fp->fh_q);
  if (fp->fh_fs) {
    dlog("Discarding filehandle for %s:%s", fp->fh_fs->fs_host, fp->fh_path);
    free_srvr(fp->fh_fs);
  }
  XFREE(fp->fh_path);
  XFREE(fp);
}