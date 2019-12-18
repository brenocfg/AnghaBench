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
struct TYPE_3__ {int /*<<< orphan*/  as_str; int /*<<< orphan*/  as_opt; } ;
typedef  TYPE_1__ amq_setopt ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_amq_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_amq_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_amq_setopt(XDR *xdrs, amq_setopt *objp)
{

  if (!xdr_amq_opt(xdrs, &objp->as_opt)) {
    return (FALSE);
  }

  if (!xdr_amq_string(xdrs, &objp->as_str)) {
    return (FALSE);
  }

  return (TRUE);
}