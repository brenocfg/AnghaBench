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
struct TYPE_3__ {int /*<<< orphan*/  sfrok_bavail; int /*<<< orphan*/  sfrok_bfree; int /*<<< orphan*/  sfrok_blocks; int /*<<< orphan*/  sfrok_bsize; int /*<<< orphan*/  sfrok_tsize; } ;
typedef  TYPE_1__ nfsstatfsokres ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_statfsokres(XDR *xdrs, nfsstatfsokres *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_statfsokres:");

  if (!xdr_u_int(xdrs, &objp->sfrok_tsize)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->sfrok_bsize)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->sfrok_blocks)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->sfrok_bfree)) {
    return (FALSE);
  }
  if (!xdr_u_int(xdrs, &objp->sfrok_bavail)) {
    return (FALSE);
  }
  return (TRUE);
}