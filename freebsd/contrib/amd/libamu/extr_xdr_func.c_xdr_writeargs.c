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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int /*<<< orphan*/  wra_len_u; int /*<<< orphan*/  wra_val_u; } ;
struct TYPE_5__ {TYPE_1__ wra_u; int /*<<< orphan*/  wra_totalcount; int /*<<< orphan*/  wra_offset; int /*<<< orphan*/  wra_beginoffset; int /*<<< orphan*/  wra_fhandle; } ;
typedef  TYPE_2__ nfswriteargs ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS_MAXDATA ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_nfs_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_writeargs(XDR *xdrs, nfswriteargs *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_writeargs:");

  if (!xdr_nfs_fh(xdrs, &objp->wra_fhandle)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->wra_beginoffset)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->wra_offset)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->wra_totalcount)) {
    return (FALSE);
  }
  if (!xdr_bytes(xdrs,
		 (char **) & objp->wra_u.wra_val_u,
		 (u_int *) & objp->wra_u.wra_len_u,
		 NFS_MAXDATA)) {
    return (FALSE);
  }
  return (TRUE);
}