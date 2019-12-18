#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xdrproc_t ;
struct TYPE_9__ {int /*<<< orphan*/  drok_attributes; int /*<<< orphan*/  drok_fhandle; } ;
struct TYPE_10__ {TYPE_1__ dr_drok_u; } ;
struct TYPE_13__ {int /*<<< orphan*/  dr_status; TYPE_2__ dr_u; } ;
typedef  TYPE_5__ nfsdiropres ;
struct TYPE_14__ {TYPE_4__* am_al; int /*<<< orphan*/ * am_transp; int /*<<< orphan*/  am_fattr; } ;
typedef  TYPE_6__ am_node ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
struct TYPE_12__ {TYPE_3__* al_mnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  mf_mount; } ;
typedef  int /*<<< orphan*/  SVC_IN_ARG_TYPE ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_OK ; 
 int /*<<< orphan*/  XFREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_to_fh (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_error (int) ; 
 int /*<<< orphan*/  svc_sendreply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcerr_systemerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_diropres ; 

void
nfs_quick_reply(am_node *mp, int error)
{
  SVCXPRT *transp = mp->am_transp;
  nfsdiropres res;
  xdrproc_t xdr_result = (xdrproc_t) xdr_diropres;

  /*
   * If there's a transp structure then we can reply to the client's
   * nfs lookup request.
   */
  if (transp) {
    if (error == 0) {
      /*
       * Construct a valid reply to a lookup request.  Same
       * code as in nfsproc_lookup_2_svc() above.
       */
      mp_to_fh(mp, &res.dr_u.dr_drok_u.drok_fhandle);
      res.dr_u.dr_drok_u.drok_attributes = mp->am_fattr;
      res.dr_status = NFS_OK;
    } else
      /*
       * Return the error that was passed to us.
       */
      res.dr_status = nfs_error(error);

    /*
     * Send off our reply
     */
    if (!svc_sendreply(transp, (XDRPROC_T_TYPE) xdr_result, (SVC_IN_ARG_TYPE) & res))
      svcerr_systemerr(transp);

    /*
     * Free up transp.  It's only used for one reply.
     */
    XFREE(mp->am_transp);
    dlog("Quick reply sent for %s", mp->am_al->al_mnt->mf_mount);
  }
}