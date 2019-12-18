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
struct TYPE_2__ {int /*<<< orphan*/  delegation; int /*<<< orphan*/  delegation_type; } ;
struct nfs_openargs {int claim; TYPE_1__ u; int /*<<< orphan*/  name; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  NFS4_OPEN_CLAIM_DELEGATE_CUR 132 
#define  NFS4_OPEN_CLAIM_DELEG_CUR_FH 131 
#define  NFS4_OPEN_CLAIM_FH 130 
#define  NFS4_OPEN_CLAIM_NULL 129 
#define  NFS4_OPEN_CLAIM_PREVIOUS 128 
 scalar_t__ decode_open_maxsz ; 
 int /*<<< orphan*/  encode_claim_delegate_cur (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_claim_delegate_cur_fh (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_claim_fh (struct xdr_stream*) ; 
 int /*<<< orphan*/  encode_claim_null (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_claim_previous (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_openhdr (struct xdr_stream*,struct nfs_openargs const*) ; 
 int /*<<< orphan*/  encode_opentype (struct xdr_stream*,struct nfs_openargs const*) ; 

__attribute__((used)) static void encode_open(struct xdr_stream *xdr, const struct nfs_openargs *arg, struct compound_hdr *hdr)
{
	encode_openhdr(xdr, arg);
	encode_opentype(xdr, arg);
	switch (arg->claim) {
	case NFS4_OPEN_CLAIM_NULL:
		encode_claim_null(xdr, arg->name);
		break;
	case NFS4_OPEN_CLAIM_PREVIOUS:
		encode_claim_previous(xdr, arg->u.delegation_type);
		break;
	case NFS4_OPEN_CLAIM_DELEGATE_CUR:
		encode_claim_delegate_cur(xdr, arg->name, &arg->u.delegation);
		break;
	case NFS4_OPEN_CLAIM_FH:
		encode_claim_fh(xdr);
		break;
	case NFS4_OPEN_CLAIM_DELEG_CUR_FH:
		encode_claim_delegate_cur_fh(xdr, &arg->u.delegation);
		break;
	default:
		BUG();
	}
	hdr->nops++;
	hdr->replen += decode_open_maxsz;
}