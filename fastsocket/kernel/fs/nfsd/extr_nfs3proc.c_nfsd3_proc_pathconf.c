#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct super_block {int s_magic; } ;
struct TYPE_8__ {TYPE_2__* fh_dentry; } ;
struct nfsd_fhandle {TYPE_3__ fh; } ;
struct nfsd3_pathconfres {int p_link_max; int p_name_max; int p_chown_restricted; int p_case_insensitive; int p_case_preserving; scalar_t__ p_no_trunc; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_7__ {TYPE_1__* d_inode; } ;
struct TYPE_6__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int EXT2_LINK_MAX ; 
 int EXT2_NAME_LEN ; 
#define  EXT2_SUPER_MAGIC 129 
#define  MSDOS_SUPER_MAGIC 128 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int /*<<< orphan*/  RETURN_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  SVCFH_fmt (TYPE_3__*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (TYPE_3__*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd3_proc_pathconf(struct svc_rqst * rqstp, struct nfsd_fhandle      *argp,
					     struct nfsd3_pathconfres *resp)
{
	__be32	nfserr;

	dprintk("nfsd: PATHCONF(3) %s\n",
				SVCFH_fmt(&argp->fh));

	/* Set default pathconf */
	resp->p_link_max = 255;		/* at least */
	resp->p_name_max = 255;		/* at least */
	resp->p_no_trunc = 0;
	resp->p_chown_restricted = 1;
	resp->p_case_insensitive = 0;
	resp->p_case_preserving = 1;

	nfserr = fh_verify(rqstp, &argp->fh, 0, NFSD_MAY_NOP);

	if (nfserr == 0) {
		struct super_block *sb = argp->fh.fh_dentry->d_inode->i_sb;

		/* Note that we don't care for remote fs's here */
		switch (sb->s_magic) {
		case EXT2_SUPER_MAGIC:
			resp->p_link_max = EXT2_LINK_MAX;
			resp->p_name_max = EXT2_NAME_LEN;
			break;
		case MSDOS_SUPER_MAGIC:
			resp->p_case_insensitive = 1;
			resp->p_case_preserving  = 0;
			break;
		}
	}

	fh_put(&argp->fh);
	RETURN_STATUS(nfserr);
}