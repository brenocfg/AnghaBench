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
struct TYPE_3__ {int /*<<< orphan*/  ne_nextentry; int /*<<< orphan*/  ne_cookie; int /*<<< orphan*/  ne_name; int /*<<< orphan*/  ne_fileid; } ;
typedef  TYPE_1__ nfsentry ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  D_XDRTRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdr_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_nfscookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_pointer (int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_entry(XDR *xdrs, nfsentry *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_entry:");

  if (!xdr_u_int(xdrs, &objp->ne_fileid)) {
    return (FALSE);
  }
  if (!xdr_filename(xdrs, &objp->ne_name)) {
    return (FALSE);
  }
  if (!xdr_nfscookie(xdrs, objp->ne_cookie)) {
    return (FALSE);
  }
  if (!xdr_pointer(xdrs, (char **) &objp->ne_nextentry, sizeof(nfsentry), (XDRPROC_T_TYPE) xdr_entry)) {
    return (FALSE);
  }
  return (TRUE);
}