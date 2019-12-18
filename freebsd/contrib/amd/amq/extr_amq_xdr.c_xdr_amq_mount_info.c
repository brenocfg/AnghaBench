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
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {int /*<<< orphan*/  mi_up; int /*<<< orphan*/  mi_refc; int /*<<< orphan*/  mi_error; int /*<<< orphan*/  mi_fserver; int /*<<< orphan*/  mi_mountinfo; int /*<<< orphan*/  mi_mountpt; int /*<<< orphan*/  mi_type; } ;
typedef  TYPE_1__ amq_mount_info ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_amq_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_amq_mount_info(XDR *xdrs, amq_mount_info *objp)
{

  if (!xdr_amq_string(xdrs, &objp->mi_type)) {
    return (FALSE);
  }

  if (!xdr_amq_string(xdrs, &objp->mi_mountpt)) {
    return (FALSE);
  }

  if (!xdr_amq_string(xdrs, &objp->mi_mountinfo)) {
    return (FALSE);
  }

  if (!xdr_amq_string(xdrs, &objp->mi_fserver)) {
    return (FALSE);
  }

  if (!xdr_int(xdrs, &objp->mi_error)) {
    return (FALSE);
  }

  if (!xdr_int(xdrs, &objp->mi_refc)) {
    return (FALSE);
  }

  if (!xdr_int(xdrs, &objp->mi_up)) {
    return (FALSE);
  }

  return (TRUE);
}