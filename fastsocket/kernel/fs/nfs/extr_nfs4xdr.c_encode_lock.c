#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct nfs_lock_args {TYPE_6__* lock_seqid; TYPE_4__* lock_stateid; int /*<<< orphan*/  lock_owner; TYPE_3__* open_stateid; TYPE_2__* open_seqid; scalar_t__ new_lock_owner; TYPE_7__* fl; scalar_t__ reclaim; int /*<<< orphan*/  block; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  void* __be32 ;
struct TYPE_15__ {int /*<<< orphan*/  fl_start; } ;
struct TYPE_14__ {TYPE_5__* sequence; } ;
struct TYPE_13__ {scalar_t__ counter; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__* sequence; } ;
struct TYPE_9__ {scalar_t__ counter; } ;

/* Variables and functions */
 int NFS4_STATEID_SIZE ; 
 scalar_t__ OP_LOCK ; 
 void* cpu_to_be32 (scalar_t__) ; 
 scalar_t__ decode_lock_maxsz ; 
 int /*<<< orphan*/  encode_lockowner (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_lock_length (TYPE_7__*) ; 
 scalar_t__ nfs4_lock_type (TYPE_7__*,int /*<<< orphan*/ ) ; 
 void** reserve_space (struct xdr_stream*,int) ; 
 void** xdr_encode_hyper (void**,int /*<<< orphan*/ ) ; 
 void** xdr_encode_opaque_fixed (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void encode_lock(struct xdr_stream *xdr, const struct nfs_lock_args *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 32);
	*p++ = cpu_to_be32(OP_LOCK);
	*p++ = cpu_to_be32(nfs4_lock_type(args->fl, args->block));
	*p++ = cpu_to_be32(args->reclaim);
	p = xdr_encode_hyper(p, args->fl->fl_start);
	p = xdr_encode_hyper(p, nfs4_lock_length(args->fl));
	*p = cpu_to_be32(args->new_lock_owner);
	if (args->new_lock_owner){
		p = reserve_space(xdr, 4+NFS4_STATEID_SIZE+4);
		*p++ = cpu_to_be32(args->open_seqid->sequence->counter);
		p = xdr_encode_opaque_fixed(p, args->open_stateid->data, NFS4_STATEID_SIZE);
		*p++ = cpu_to_be32(args->lock_seqid->sequence->counter);
		encode_lockowner(xdr, &args->lock_owner);
	}
	else {
		p = reserve_space(xdr, NFS4_STATEID_SIZE+4);
		p = xdr_encode_opaque_fixed(p, args->lock_stateid->data, NFS4_STATEID_SIZE);
		*p = cpu_to_be32(args->lock_seqid->sequence->counter);
	}
	hdr->nops++;
	hdr->replen += decode_lock_maxsz;
}