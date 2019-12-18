#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct qstr {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ nfs4_stateid ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OPEN_CLAIM_DELEGATE_CUR ; 
 scalar_t__ NFS4_STATEID_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_string (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void encode_claim_delegate_cur(struct xdr_stream *xdr, const struct qstr *name, const nfs4_stateid *stateid)
{
	__be32 *p;

	p = reserve_space(xdr, 4+NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(NFS4_OPEN_CLAIM_DELEGATE_CUR);
	xdr_encode_opaque_fixed(p, stateid->data, NFS4_STATEID_SIZE);
	encode_string(xdr, name->len, name->name);
}