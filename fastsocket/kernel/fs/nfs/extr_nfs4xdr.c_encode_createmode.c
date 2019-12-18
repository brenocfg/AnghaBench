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
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  verifier; struct iattr* attrs; } ;
struct nfs_openargs {int createmode; int /*<<< orphan*/  server; TYPE_1__ u; } ;
struct iattr {int /*<<< orphan*/  ia_valid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  NFS4_CREATE_EXCLUSIVE 131 
#define  NFS4_CREATE_EXCLUSIVE4_1 130 
#define  NFS4_CREATE_GUARDED 129 
#define  NFS4_CREATE_UNCHECKED 128 
 int /*<<< orphan*/  cpu_to_be32 (int const) ; 
 int /*<<< orphan*/  encode_attrs (struct xdr_stream*,struct iattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs4_verifier (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static inline void encode_createmode(struct xdr_stream *xdr, const struct nfs_openargs *arg)
{
	struct iattr dummy;
	__be32 *p;

	p = reserve_space(xdr, 4);
	switch(arg->createmode) {
	case NFS4_CREATE_UNCHECKED:
		*p = cpu_to_be32(NFS4_CREATE_UNCHECKED);
		encode_attrs(xdr, arg->u.attrs, arg->server);
		break;
	case NFS4_CREATE_GUARDED:
		*p = cpu_to_be32(NFS4_CREATE_GUARDED);
		encode_attrs(xdr, arg->u.attrs, arg->server);
		break;
	case NFS4_CREATE_EXCLUSIVE:
		*p = cpu_to_be32(NFS4_CREATE_EXCLUSIVE);
		encode_nfs4_verifier(xdr, &arg->u.verifier);
		break;
	case NFS4_CREATE_EXCLUSIVE4_1:
		*p = cpu_to_be32(NFS4_CREATE_EXCLUSIVE4_1);
		encode_nfs4_verifier(xdr, &arg->u.verifier);
		dummy.ia_valid = 0;
		encode_attrs(xdr, &dummy, arg->server);
	}
}