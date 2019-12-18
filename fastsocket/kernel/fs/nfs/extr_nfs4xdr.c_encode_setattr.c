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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfs_setattrargs {int /*<<< orphan*/  iap; TYPE_1__ stateid; } ;
struct nfs_server {int dummy; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFS4_STATEID_SIZE ; 
 int /*<<< orphan*/  OP_SETATTR ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_setattr_maxsz ; 
 int /*<<< orphan*/  encode_attrs (struct xdr_stream*,int /*<<< orphan*/ ,struct nfs_server const*) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void encode_setattr(struct xdr_stream *xdr, const struct nfs_setattrargs *arg, const struct nfs_server *server, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4+NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(OP_SETATTR);
	xdr_encode_opaque_fixed(p, arg->stateid.data, NFS4_STATEID_SIZE);
	hdr->nops++;
	hdr->replen += decode_setattr_maxsz;
	encode_attrs(xdr, arg->iap, server);
}