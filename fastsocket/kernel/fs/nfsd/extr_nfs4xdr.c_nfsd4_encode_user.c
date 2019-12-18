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
struct svc_rqst {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_ACL_WHO_NAMED ; 
 int /*<<< orphan*/  nfsd4_encode_name (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static inline __be32
nfsd4_encode_user(struct svc_rqst *rqstp, uid_t uid, __be32 **p, int *buflen)
{
	return nfsd4_encode_name(rqstp, NFS4_ACL_WHO_NAMED, uid, 0, p, buflen);
}