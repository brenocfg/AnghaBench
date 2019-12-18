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
struct TYPE_4__ {int /*<<< orphan*/  sfr_reply_u; } ;
struct TYPE_5__ {int sfr_status; TYPE_1__ sfr_u; } ;
typedef  TYPE_2__ nfsstatfsres ;
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
 int /*<<< orphan*/  xdr_nfsstat (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xdr_statfsokres (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_statfsres(XDR *xdrs, nfsstatfsres *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_statfsres:");

  if (!xdr_nfsstat(xdrs, &objp->sfr_status)) {
    return (FALSE);
  }
  switch (objp->sfr_status) {
  case NFS_OK:
    if (!xdr_statfsokres(xdrs, &objp->sfr_u.sfr_reply_u)) {
      return (FALSE);
    }
    break;
  default:
    break;
  }
  return (TRUE);
}