#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  amq_mount_tree ;
struct TYPE_9__ {long s_mtime; int /*<<< orphan*/  s_statfs; int /*<<< orphan*/  s_readlink; int /*<<< orphan*/  s_readdir; int /*<<< orphan*/  s_lookup; int /*<<< orphan*/  s_getattr; int /*<<< orphan*/  s_uid; } ;
struct TYPE_10__ {TYPE_4__ am_stats; TYPE_3__* am_al; scalar_t__ am_link; scalar_t__ am_path; } ;
typedef  TYPE_5__ am_node ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_8__ {TYPE_2__* al_mnt; } ;
struct TYPE_7__ {TYPE_1__* mf_ops; scalar_t__ mf_mount; scalar_t__ mf_info; } ;
struct TYPE_6__ {scalar_t__ fs_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_amq_string (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_long (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  xdr_u_short (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_amq_mount_tree_node(XDR *xdrs, amq_mount_tree *objp)
{
  am_node *mp = (am_node *) objp;
  long mtime;

  if (!xdr_amq_string(xdrs, &mp->am_al->al_mnt->mf_info)) {
    return (FALSE);
  }
  if (!xdr_amq_string(xdrs, &mp->am_path)) {
    return (FALSE);
  }
  if (!xdr_amq_string(xdrs, mp->am_link ? &mp->am_link : &mp->am_al->al_mnt->mf_mount)) {
    return (FALSE);
  }
  if (!xdr_amq_string(xdrs, &mp->am_al->al_mnt->mf_ops->fs_type)) {
    return (FALSE);
  }
  mtime = mp->am_stats.s_mtime;
  if (!xdr_long(xdrs, &mtime)) {
    return (FALSE);
  }
  if (!xdr_u_short(xdrs, &mp->am_stats.s_uid)) {
    return (FALSE);
  }
  if (!xdr_int(xdrs, &mp->am_stats.s_getattr)) {
    return (FALSE);
  }
  if (!xdr_int(xdrs, &mp->am_stats.s_lookup)) {
    return (FALSE);
  }
  if (!xdr_int(xdrs, &mp->am_stats.s_readdir)) {
    return (FALSE);
  }
  if (!xdr_int(xdrs, &mp->am_stats.s_readlink)) {
    return (FALSE);
  }
  if (!xdr_int(xdrs, &mp->am_stats.s_statfs)) {
    return (FALSE);
  }
  return (TRUE);
}