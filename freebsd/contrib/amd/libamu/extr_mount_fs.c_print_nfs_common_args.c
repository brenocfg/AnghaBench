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
struct nfs_common_args {int /*<<< orphan*/  acdirmax; int /*<<< orphan*/  acdirmin; int /*<<< orphan*/  acregmax; int /*<<< orphan*/  acregmin; int /*<<< orphan*/  retrans; int /*<<< orphan*/  timeo; int /*<<< orphan*/  wsize; int /*<<< orphan*/  rsize; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_DEBUG ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_nfs_common_args(const struct nfs_common_args *a)
{
  plog(XLOG_DEBUG, "NA->flags = 0x%lx", a->flags);

  plog(XLOG_DEBUG, "NA->rsize = %lu", a->rsize);
  plog(XLOG_DEBUG, "NA->wsize = %lu", a->wsize);
  plog(XLOG_DEBUG, "NA->timeo = %lu", a->timeo);
  plog(XLOG_DEBUG, "NA->retrans = %lu", a->retrans);

#ifdef HAVE_NFS_ARGS_T_ACREGMIN
  plog(XLOG_DEBUG, "NA->acregmin = %lu", a->acregmin);
  plog(XLOG_DEBUG, "NA->acregmax = %lu", a->acregmax);
  plog(XLOG_DEBUG, "NA->acdirmin = %lu", a->acdirmin);
  plog(XLOG_DEBUG, "NA->acdirmax = %lu", a->acdirmax);
#endif /* HAVE_NFS_ARGS_T_ACREGMIN */
}