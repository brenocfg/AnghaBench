#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_8__ {scalar_t__ mf_private; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_9__ {TYPE_4__** kvhash; } ;
typedef  TYPE_3__ mnt_map ;
struct TYPE_10__ {int /*<<< orphan*/  key; struct TYPE_10__* next; } ;
typedef  TYPE_4__ kv ;
struct TYPE_11__ {TYPE_1__* am_al; } ;
typedef  TYPE_5__ am_node ;
struct TYPE_7__ {TYPE_2__* al_mnt; } ;

/* Variables and functions */
 size_t NKVHASH ; 

__attribute__((used)) static void
count_map_entries(const am_node *mp, u_int *out_blocks, u_int *out_bfree, u_int *out_bavail)
{
  u_int blocks, bfree, bavail, i;
  mntfs *mf;
  mnt_map *mmp;
  kv *k;

  blocks = bfree = bavail = 0;
  if (!mp)
    goto out;
  mf = mp->am_al->al_mnt;
  if (!mf)
    goto out;
  mmp = (mnt_map *) mf->mf_private;
  if (!mmp)
    goto out;

  /* iterate over keys */
  for (i = 0; i < NKVHASH; i++) {
    for (k = mmp->kvhash[i]; k ; k = k->next) {
      if (!k->key)
	continue;
      blocks++;
      /*
       * XXX: Need to count how many are actively in use and recompute
       * bfree and bavail based on it.
       */
    }
  }

out:
  *out_blocks = blocks;
  *out_bfree = bfree;
  *out_bavail = bavail;
}