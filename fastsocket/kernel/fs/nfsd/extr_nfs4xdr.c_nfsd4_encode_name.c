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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u8 ;
struct svc_rqst {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IDMAP_NAMESZ ; 
 int NFS4_ACL_WHO_NAMED ; 
 int XDR_QUADLEN (int) ; 
 int nfs4_acl_write_who (int,int /*<<< orphan*/ *) ; 
 int nfsd_map_gid_to_name (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfsd_map_uid_to_name (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_name(struct svc_rqst *rqstp, int whotype, uid_t id, int group,
			__be32 **p, int *buflen)
{
	int status;

	if (*buflen < (XDR_QUADLEN(IDMAP_NAMESZ) << 2) + 4)
		return nfserr_resource;
	if (whotype != NFS4_ACL_WHO_NAMED)
		status = nfs4_acl_write_who(whotype, (u8 *)(*p + 1));
	else if (group)
		status = nfsd_map_gid_to_name(rqstp, id, (u8 *)(*p + 1));
	else
		status = nfsd_map_uid_to_name(rqstp, id, (u8 *)(*p + 1));
	if (status < 0)
		return nfserrno(status);
	*p = xdr_encode_opaque(*p, NULL, status);
	*buflen -= (XDR_QUADLEN(status) << 2) + 4;
	BUG_ON(*buflen < 0);
	return 0;
}