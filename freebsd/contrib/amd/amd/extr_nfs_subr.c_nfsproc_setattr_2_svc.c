#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sag_fhandle; } ;
typedef  TYPE_1__ nfssattrargs ;
struct TYPE_6__ {void* ns_status; } ;
typedef  TYPE_2__ nfsattrstat ;

/* Variables and functions */
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  fh_to_mp (int /*<<< orphan*/ *) ; 
 void* nfs_error (int /*<<< orphan*/ ) ; 

nfsattrstat *
nfsproc_setattr_2_svc(nfssattrargs *argp, struct svc_req *rqstp)
{
  static nfsattrstat res;

  if (!fh_to_mp(&argp->sag_fhandle))
    res.ns_status = nfs_error(ESTALE);
  else
    res.ns_status = nfs_error(EROFS);

  return &res;
}