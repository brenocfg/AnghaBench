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
struct TYPE_3__ {scalar_t__ fhs_status; int /*<<< orphan*/  fhs_fh; } ;
typedef  TYPE_1__ fhstatus ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,scalar_t__*) ; 

bool_t
xdr_fhstatus(XDR *xdrs, fhstatus *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_fhstatus:");

  if (!xdr_u_int(xdrs, &objp->fhs_status)) {
    return (FALSE);
  }
  if (objp->fhs_status == 0 && !xdr_fhandle(xdrs, objp->fhs_fh)) {
    return (FALSE);
  }
  return (TRUE);
}