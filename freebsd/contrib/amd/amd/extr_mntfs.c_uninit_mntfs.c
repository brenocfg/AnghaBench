#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mf_cid; scalar_t__ mf_server; scalar_t__ mf_mount; scalar_t__ mf_private; int /*<<< orphan*/  (* mf_prfree ) (scalar_t__) ;scalar_t__ mf_info; scalar_t__ mf_remopts; scalar_t__ mf_mopts; scalar_t__ mf_auto; scalar_t__ mf_fo; } ;
typedef  TYPE_1__ mntfs ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (scalar_t__) ; 
 int /*<<< orphan*/  free_opts (scalar_t__) ; 
 int /*<<< orphan*/  free_srvr (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  untimeout (scalar_t__) ; 

__attribute__((used)) static void
uninit_mntfs(mntfs *mf)
{
  if (mf->mf_fo) {
    free_opts(mf->mf_fo);
    XFREE(mf->mf_fo);
  }
  XFREE(mf->mf_auto);
  XFREE(mf->mf_mopts);
  XFREE(mf->mf_remopts);
  XFREE(mf->mf_info);
  if (mf->mf_private && mf->mf_prfree)
    (*mf->mf_prfree) (mf->mf_private);

  XFREE(mf->mf_mount);

  /*
   * Clean up the file server
   */
  if (mf->mf_server)
    free_srvr(mf->mf_server);

  /*
   * Don't do a callback on this mount
   */
  if (mf->mf_cid) {
    untimeout(mf->mf_cid);
    mf->mf_cid = 0;
  }
}