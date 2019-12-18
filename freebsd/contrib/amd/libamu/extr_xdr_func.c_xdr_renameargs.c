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
struct TYPE_3__ {int /*<<< orphan*/  rna_to; int /*<<< orphan*/  rna_from; } ;
typedef  TYPE_1__ nfsrenameargs ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_diropargs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_renameargs(XDR *xdrs, nfsrenameargs *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_renameargs:");

  if (!xdr_diropargs(xdrs, &objp->rna_from)) {
    return (FALSE);
  }
  if (!xdr_diropargs(xdrs, &objp->rna_to)) {
    return (FALSE);
  }
  return (TRUE);
}