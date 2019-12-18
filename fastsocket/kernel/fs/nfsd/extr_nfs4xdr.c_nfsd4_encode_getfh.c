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
struct TYPE_2__ {unsigned int fh_size; int /*<<< orphan*/  fh_base; } ;
struct svc_fh {TYPE_1__ fh_handle; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  RESERVE_SPACE (unsigned int) ; 
 int /*<<< orphan*/  WRITE32 (unsigned int) ; 
 int /*<<< orphan*/  WRITEMEM (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static __be32
nfsd4_encode_getfh(struct nfsd4_compoundres *resp, __be32 nfserr, struct svc_fh **fhpp)
{
	struct svc_fh *fhp = *fhpp;
	unsigned int len;
	__be32 *p;

	if (!nfserr) {
		len = fhp->fh_handle.fh_size;
		RESERVE_SPACE(len + 4);
		WRITE32(len);
		WRITEMEM(&fhp->fh_handle.fh_base, len);
		ADJUST_ARGS();
	}
	return nfserr;
}