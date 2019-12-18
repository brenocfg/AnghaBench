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
struct TYPE_2__ {int fh_size; int /*<<< orphan*/  fh_base; } ;
struct svc_fh {TYPE_1__ fh_handle; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS_FHSIZE ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __be32 *
decode_fh(__be32 *p, struct svc_fh *fhp)
{
	fh_init(fhp, NFS_FHSIZE);
	memcpy(&fhp->fh_handle.fh_base, p, NFS_FHSIZE);
	fhp->fh_handle.fh_size = NFS_FHSIZE;

	/* FIXME: Look up export pointer here and verify
	 * Sun Secure RPC if requested */
	return p + (NFS_FHSIZE >> 2);
}