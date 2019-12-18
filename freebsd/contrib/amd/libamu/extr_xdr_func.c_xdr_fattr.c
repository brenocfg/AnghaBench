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
struct TYPE_3__ {int /*<<< orphan*/  na_ctime; int /*<<< orphan*/  na_mtime; int /*<<< orphan*/  na_atime; int /*<<< orphan*/  na_fileid; int /*<<< orphan*/  na_fsid; int /*<<< orphan*/  na_blocks; int /*<<< orphan*/  na_rdev; int /*<<< orphan*/  na_blocksize; int /*<<< orphan*/  na_size; int /*<<< orphan*/  na_gid; int /*<<< orphan*/  na_uid; int /*<<< orphan*/  na_nlink; int /*<<< orphan*/  na_mode; int /*<<< orphan*/  na_type; } ;
typedef  TYPE_1__ nfsfattr ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_ftype (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_nfstime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_fattr(XDR *xdrs, nfsfattr *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_fattr:");

  if (!xdr_ftype(xdrs, &objp->na_type)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_mode)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_nlink)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_uid)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_gid)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_size)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_blocksize)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_rdev)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_blocks)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_fsid)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->na_fileid)) {
    return (FALSE);
  }
  if (!xdr_nfstime(xdrs, &objp->na_atime)) {
    return (FALSE);
  }
  if (!xdr_nfstime(xdrs, &objp->na_mtime)) {
    return (FALSE);
  }
  if (!xdr_nfstime(xdrs, &objp->na_ctime)) {
    return (FALSE);
  }
  return (TRUE);
}