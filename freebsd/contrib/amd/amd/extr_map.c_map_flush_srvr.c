#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fs_host; } ;
typedef  TYPE_3__ fserver ;
struct TYPE_10__ {int /*<<< orphan*/  am_ttl; int /*<<< orphan*/  am_path; TYPE_1__* am_al; } ;
typedef  TYPE_4__ am_node ;
struct TYPE_8__ {TYPE_3__* mf_server; } ;
struct TYPE_7__ {TYPE_2__* al_mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  clocktime (int /*<<< orphan*/ *) ; 
 TYPE_4__** exported_ap ; 
 int last_used_map ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_timeout_mp () ; 

void
map_flush_srvr(fserver *fs)
{
  int i;
  int done = 0;

  for (i = last_used_map; i >= 0; --i) {
    am_node *mp = exported_ap[i];

    if (mp && mp->am_al->al_mnt && mp->am_al->al_mnt->mf_server == fs) {
      plog(XLOG_INFO, "Flushed %s; dependent on %s", mp->am_path, fs->fs_host);
      mp->am_ttl = clocktime(NULL);
      done = 1;
    }
  }
  if (done)
    reschedule_timeout_mp();
}