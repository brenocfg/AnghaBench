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
struct xdr_stream {int dummy; } ;
struct nfs_openargs {int /*<<< orphan*/  id; TYPE_3__* server; int /*<<< orphan*/  clientid; int /*<<< orphan*/  fmode; TYPE_2__* seqid; } ;
typedef  void* __be32 ;
struct TYPE_6__ {int s_dev; } ;
struct TYPE_5__ {TYPE_1__* sequence; } ;
struct TYPE_4__ {int counter; } ;

/* Variables and functions */
 int OP_OPEN ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  encode_share_access (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 void** reserve_space (struct xdr_stream*,int) ; 
 void** xdr_encode_hyper (void**,int /*<<< orphan*/ ) ; 
 void** xdr_encode_opaque_fixed (void**,char*,int) ; 

__attribute__((used)) static inline void encode_openhdr(struct xdr_stream *xdr, const struct nfs_openargs *arg)
{
	__be32 *p;
 /*
 * opcode 4, seqid 4, share_access 4, share_deny 4, clientid 8, ownerlen 4,
 * owner 4 = 32
 */
	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(OP_OPEN);
	*p = cpu_to_be32(arg->seqid->sequence->counter);
	encode_share_access(xdr, arg->fmode);
	p = reserve_space(xdr, 32);
	p = xdr_encode_hyper(p, arg->clientid);
	*p++ = cpu_to_be32(20);
	p = xdr_encode_opaque_fixed(p, "open id:", 8);
	*p++ = cpu_to_be32(arg->server->s_dev);
	xdr_encode_hyper(p, arg->id);
}