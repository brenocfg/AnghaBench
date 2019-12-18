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
struct TYPE_4__ {int /*<<< orphan*/  rlr_data_u; } ;
struct TYPE_5__ {int rlr_status; TYPE_1__ rlr_u; } ;
typedef  TYPE_2__ nfsreadlinkres ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
#define  NFS_OK 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_nfspath (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_nfsstat (int /*<<< orphan*/ *,int*) ; 

bool_t
xdr_readlinkres(XDR *xdrs, nfsreadlinkres *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_readlinkres:");

  if (!xdr_nfsstat(xdrs, &objp->rlr_status)) {
    return (FALSE);
  }
  switch (objp->rlr_status) {
  case NFS_OK:
    if (!xdr_nfspath(xdrs, &objp->rlr_u.rlr_data_u)) {
      return (FALSE);
    }
    break;
  default:
    break;
  }
  return (TRUE);
}