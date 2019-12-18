#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  amq_mount_tree_p ;
typedef  int /*<<< orphan*/  amq_mount_tree ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ xdr_amq_mount_tree ; 
 int /*<<< orphan*/  xdr_pointer (int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ ) ; 

bool_t
xdr_amq_mount_tree_p(XDR *xdrs, amq_mount_tree_p *objp)
{
  if (!xdr_pointer(xdrs,
		   (char **) objp,
		   sizeof(amq_mount_tree),
		   (XDRPROC_T_TYPE) xdr_amq_mount_tree)) {
    return (FALSE);
  }
  return (TRUE);
}