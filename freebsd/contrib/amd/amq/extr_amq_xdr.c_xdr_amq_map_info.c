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
struct TYPE_3__ {int /*<<< orphan*/  mi_up; int /*<<< orphan*/  mi_refc; int /*<<< orphan*/  mi_reloads; int /*<<< orphan*/  mi_nentries; int /*<<< orphan*/  mi_flags; int /*<<< orphan*/  mi_modify; int /*<<< orphan*/  mi_wildcard; int /*<<< orphan*/  mi_name; } ;
typedef  TYPE_1__ amq_map_info ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_amq_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_time_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_amq_map_info(XDR *xdrs, amq_map_info *objp)
{
  if (!xdr_amq_string(xdrs, &objp->mi_name)) {
    return (FALSE);
  }

  if (!xdr_amq_string(xdrs, &objp->mi_wildcard)) {
    return (FALSE);
  }

  if (!xdr_time_type(xdrs, &objp->mi_modify)) {
    return (FALSE);
  }

  if (!xdr_int(xdrs, &objp->mi_flags)) {
    return (FALSE);
  }

  if (!xdr_int(xdrs, &objp->mi_nentries)) {
    return (FALSE);
  }

  if (!xdr_int(xdrs, &objp->mi_reloads)) {
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