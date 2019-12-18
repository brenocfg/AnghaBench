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
struct TYPE_3__ {int /*<<< orphan*/  ex_next; int /*<<< orphan*/  ex_groups; int /*<<< orphan*/  ex_dir; } ;
typedef  TYPE_1__ exportnode ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_dirpath (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_exports (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_exportnode(XDR *xdrs, exportnode *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_exportnode:");

  if (!xdr_dirpath(xdrs, &objp->ex_dir)) {
    return (FALSE);
  }
  if (!xdr_groups(xdrs, &objp->ex_groups)) {
    return (FALSE);
  }
  if (!xdr_exports(xdrs, &objp->ex_next)) {
    return (FALSE);
  }
  return (TRUE);
}