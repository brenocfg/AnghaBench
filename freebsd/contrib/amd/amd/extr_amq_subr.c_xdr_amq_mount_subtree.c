#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ voidp ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  amq_mount_tree ;
struct TYPE_2__ {int /*<<< orphan*/  am_child; int /*<<< orphan*/  am_osib; } ;
typedef  TYPE_1__ am_node ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_amq_mount_tree_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_pointer (int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ ) ; 

bool_t
xdr_amq_mount_subtree(XDR *xdrs, amq_mount_tree *objp)
{
  am_node *mp = (am_node *) objp;

  if (!xdr_amq_mount_tree_node(xdrs, objp)) {
    return (FALSE);
  }
  if (!xdr_pointer(xdrs,
		   (char **) ((voidp) &mp->am_osib),
		   sizeof(amq_mount_tree),
		   (XDRPROC_T_TYPE) xdr_amq_mount_subtree)) {
    return (FALSE);
  }
  if (!xdr_pointer(xdrs,
		   (char **) ((voidp) &mp->am_child),
		   sizeof(amq_mount_tree),
		   (XDRPROC_T_TYPE) xdr_amq_mount_subtree)) {
    return (FALSE);
  }
  return (TRUE);
}