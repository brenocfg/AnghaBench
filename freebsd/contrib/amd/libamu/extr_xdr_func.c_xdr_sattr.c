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
struct TYPE_3__ {int /*<<< orphan*/  sa_mtime; int /*<<< orphan*/  sa_atime; int /*<<< orphan*/  sa_size; int /*<<< orphan*/  sa_gid; int /*<<< orphan*/  sa_uid; int /*<<< orphan*/  sa_mode; } ;
typedef  TYPE_1__ nfssattr ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_nfstime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_sattr(XDR *xdrs, nfssattr *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_sattr:");

  if (!xdr_u_int(xdrs, &objp->sa_mode)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->sa_uid)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->sa_gid)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->sa_size)) {
    return (FALSE);
  }
  if (!xdr_nfstime(xdrs, &objp->sa_atime)) {
    return (FALSE);
  }
  if (!xdr_nfstime(xdrs, &objp->sa_mtime)) {
    return (FALSE);
  }
  return (TRUE);
}