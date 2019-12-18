#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfs4_sequence_args {TYPE_3__* sa_session; } ;
struct TYPE_6__ {TYPE_2__* clp; } ;
struct TYPE_5__ {TYPE_1__* cl_mvops; } ;
struct TYPE_4__ {int /*<<< orphan*/  minor_version; } ;

/* Variables and functions */

__attribute__((used)) static u32 nfs4_xdr_minorversion(const struct nfs4_sequence_args *args)
{
#if defined(CONFIG_NFS_V4_1)
	if (args->sa_session)
		return args->sa_session->clp->cl_mvops->minor_version;
#endif /* CONFIG_NFS_V4_1 */
	return 0;
}