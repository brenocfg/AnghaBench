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
struct TYPE_4__ {int /*<<< orphan*/  raok_len_u; int /*<<< orphan*/  raok_val_u; } ;
struct TYPE_5__ {TYPE_1__ raok_u; int /*<<< orphan*/  raok_attributes; } ;
typedef  TYPE_2__ nfsreadokres ;
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
 int /*<<< orphan*/  xdr_fattr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_readokres(XDR *xdrs, nfsreadokres *objp)
{
  if (amuDebug(D_XDRTRACE))
    plog(XLOG_DEBUG, "xdr_readokres:");

  if (!xdr_fattr(xdrs, &objp->raok_attributes)) {
    return (FALSE);
  }
  if (!xdr_bytes(xdrs,
		 (char **) & objp->raok_u.raok_val_u,
		 (u_int *) & objp->raok_u.raok_len_u,
		 NFS_MAXDATA)) {
    return (FALSE);
  }
  return (TRUE);
}