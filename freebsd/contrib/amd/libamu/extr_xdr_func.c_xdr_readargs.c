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
struct TYPE_3__ {int /*<<< orphan*/  ra_totalcount; int /*<<< orphan*/  ra_count; int /*<<< orphan*/  ra_offset; int /*<<< orphan*/  ra_fhandle; } ;
typedef  TYPE_1__ nfsreadargs ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_nfs_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_readargs(XDR *xdrs, nfsreadargs *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_readargs:");

  if (!xdr_nfs_fh(xdrs, &objp->ra_fhandle)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->ra_offset)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->ra_count)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->ra_totalcount)) {
    return (FALSE);
  }
  return (TRUE);
}